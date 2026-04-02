/*
Copyright (c) 2025-2026 Orkiin

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "uiterm.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#if defined(WINDOWS)
#include <windows.h>
#else
#include <termios.h>
#endif // defined

// TODO: Implementar visobilidad de cartas por cursor

#define ESCAPESECUENCE "\033["
#define ALTERNATE_BUFFER ESCAPESECUENCE "?1049h"
#define ORIGINAL_BUFFER ESCAPESECUENCE "?1049l"
#define HIDE_CURSOR ESCAPESECUENCE "?25l"
#define SHOW_CURSOR ESCAPESECUENCE "?25h"
#define CLEAR_SCREEN ESCAPESECUENCE "2J"
#define BUFFER_HOME ESCAPESECUENCE "H"

#define NORMAL_BG ESCAPESECUENCE "47m"
#define SELECTED_BG ESCAPESECUENCE "44m"
#define COLOR_RED ESCAPESECUENCE "31m"
#define COLOR_BLACK ESCAPESECUENCE "30m"
#define RESET_DEFAULT_COLOR ESCAPESECUENCE "0m"

#define STR_CARD_COLOR(c) (IS_RED_SUIT((c).s) ? COLOR_RED : COLOR_BLACK)

#if defined(WINDOWS)

HANDLE hStdin, hStdout;
DWORD fdwSaveOldMode;
CONSOLE_SCREEN_BUFFER_INFO csbi;

void restore() {
  printf(SHOW_CURSOR);
  printf(ORIGINAL_BUFFER);
  fflush(stdout);
  SetConsoleMode(hStdin, fdwSaveOldMode);
}

void setup() {
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleMode(hStdin, &fdwSaveOldMode);
  DWORD rawmode = ENABLE_EXTENDED_FLAGS;
  SetConsoleMode(hStdin, rawmode);
  system("cls");
  printf(ALTERNATE_BUFFER "\n");
  printf(HIDE_CURSOR);
  printf(CLEAR_SCREEN);
  printf(BUFFER_HOME);
  fflush(stdout);
  atexit(restore);
}
#else
static struct termios original_termios;

void restore() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
  printf(SHOW_CURSOR);
  printf(ORIGINAL_BUFFER);
  fflush(stdout);
}

void setup() {
  struct termios new_termios;
  tcgetattr(STDIN_FILENO, &original_termios);
  new_termios = original_termios;
  new_termios.c_lflag &= ~(ICANON | ECHO);
  new_termios.c_cc[VMIN] = 1;
  new_termios.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);
  printf(ALTERNATE_BUFFER "\n");
  printf(HIDE_CURSOR);
  printf(CLEAR_SCREEN);
  printf(BUFFER_HOME);
  fflush(stdout);
  atexit(restore);
}
#endif // defined

void show_card(card a, card_state state) {
  char *suitdisplay[] = {"♥", "♦", "♣", "♠"};
  char *rankdisplay[] = {"A", "2", "3",  "4", "5", "6", "7",
                         "8", "9", "10", "J", "Q", "K"};

  switch (state) {
  case NONE:
    printf("   ");
    break;
  case EMPTY:
    printf("[O]");
    break;
  case HIDDEN:
    printf("▓▓▓");
    break;
  case SELECTED:
  case GROUP_SELECTED:
    printf(SELECTED_BG "%s%2s%s" RESET_DEFAULT_COLOR, STR_CARD_COLOR(a),
           rankdisplay[a.r], suitdisplay[a.s]);
    break;
  case VISIBLE:
  case SIDE_STACKED:
    printf(NORMAL_BG "%s%2s%s" RESET_DEFAULT_COLOR, STR_CARD_COLOR(a),
           rankdisplay[a.r], suitdisplay[a.s]);
    break;
  }
}

void show_side_stack(card_stack *stack) {
  for (size_t index = 0; index < ((stack->number < 1) ? 0 : 1); index++) {
    show_card(stack->cards[((stack->front + index) % (stack->capacity))],
              VISIBLE);
  }
  for (size_t index = 1; index < stack->number; index++) {
    show_card(stack->cards[((stack->front + index) % (stack->capacity))],
              VISIBLE);
  }
}

void show_deck(card_stack *stack) {
  for (size_t index = 0; index < stack->number; index++) {
    show_card(stack->cards[((stack->front + index) % (stack->capacity))],
              VISIBLE);
    printf(((index % 13) == 12) ? "\n\n" : " ");
  }
  printf("\n");
}

void show_fundation(card_stack *fundation) {
  card a = ppeek(fundation);
  show_card(a, ((COMPARE_EQ(a, INVALID_CARD)) ? EMPTY : VISIBLE));
}

void show_tableau(card_stack *tableau, size_t row) {
  if (row == 0 && tableau->number == 0) {
    show_card(INVALID_CARD, EMPTY);
  } else if (row >= tableau->number) {
    show_card(INVALID_CARD, NONE);
  } else if (row < tableau->front) {
    show_card(tableau->cards[row], HIDDEN);
    //} else if (row == tableau->number - 1) {
    // show_card(tableau->cards[row], SELECTED);
  } else {
    show_card(tableau->cards[row], VISIBLE);
  }
}

void show_window(card_stack *window) {
  // Making sure of correct alignment with space
  printf("  ");
  switch (window->number) {
  case 1:
    show_card(INVALID_CARD, NONE);
  // show_card with none will print the corresponding space
  // for proper right justification of the cards and since
  // we will need to print 2 card spaces if there isonly one
  // card on the window this falthrough is intentional
  case 2:
    show_card(INVALID_CARD, NONE);
  // Now this falthrough is also intentional becuase in the
  // next case the window is shown with the correct number
  // of cards without taking extra spaces to acount for
  // total capacity. I would have loved to use something
  // similar to show the case when it is empty, maybe later
  // I will revisit and think of something clever to do in here
  case 3:
    show_side_stack(window);
    break;
  default:
    show_card(INVALID_CARD, NONE);
    show_card(INVALID_CARD, NONE);
    show_card(INVALID_CARD, EMPTY);
    break;
  }
}

void show_stock(card_stack *stack) {
  if (!stack->number)
    show_card(INVALID_CARD, EMPTY);
  else
    show_card(INVALID_CARD, HIDDEN);
}

void show_hand(card_stack *hand) {
  switch (hand->number) {
  case 0:
    show_card(INVALID_CARD, NONE);
    break;
  case 1:
    show_card(ppeek(hand), VISIBLE);
    break;
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
    show_card(ppeek(hand), VISIBLE);
    printf("▓");
    break;
  }
}

void show_menu(menu_t *menu_state) {
  printf(CLEAR_SCREEN BUFFER_HOME);
  for (size_t line = 0; line < menu_state->options_number; line++) {
    if (line == menu_state->current_index)
      printf((menu_state->game->dif == EASY) ? SELECTED_BG COLOR_BLACK
                                             : NORMAL_BG COLOR_RED);
    printf("%-25s" RESET_DEFAULT_COLOR "\n",
           menu_state->option[line].option_text);
  }
}

void show_game_state(game_state_solitary *game) {
  printf(CLEAR_SCREEN);
  printf(BUFFER_HOME);
  fflush(stdout);
  for (size_t i = 0; i < 4; i++) {
    show_fundation(&(game->fundation[i]));
    printf(" ");
  }
  show_window(&(game->window));
  show_stock(&(game->stock));
  printf("\n\n");
  for (size_t row = 0; row < 19; row++) {
    for (size_t i = 0; i < 7; i++) {
      show_tableau(&(game->tableau[i]), row);
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
  show_hand(&(game->hand));
  fflush(stdout);
}

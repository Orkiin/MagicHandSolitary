#include "uiterm.h"

#define NORMAL_BG "\033[47m"
#define SELECTED_BG "\033[44m"
#define COLOR_RED "\033[31m"
#define COLOR_BLACK "\033[30m"
#define RESET_DEFAULT_OLOR "\033[0m"

#define STR_CARD_COLOR(c) (IS_RED_SUIT((c).s) ? COLOR_RED : COLOR_BLACK)

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
    printf(SELECTED_BG "%s%2s%s" RESET_DEFAULT_OLOR, STR_CARD_COLOR(a),
           rankdisplay[a.r], suitdisplay[a.s]);
    break;
  case VISIBLE:
  case SIDE_STACKED:
    printf(NORMAL_BG "%s%2s%s" RESET_DEFAULT_OLOR, STR_CARD_COLOR(a),
           rankdisplay[a.r], suitdisplay[a.s]);
    break;
  }
}

void show_side_stack(card_stack *stack) {
  for (size_t index = 0; index < ((stack->number < 1) ? 0 : 1); index++) {
    show_card(stack->cards[((stack->front + index) % (stack->capacity))],
              SELECTED);
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

void show_hand(card_stack *hand){
  switch(hand->number){
    case 0:
      break;
    case 1:
      show_fundation(hand);
      break;
    defaukt:
      show_fundation(hand);
      printf("▓");
    break;
  }
}

void show_game_state(game_state_solitary *game) {
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
  printf("\n");
}

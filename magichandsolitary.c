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
#include "magichandsolitary.h"
#include "cards.h"
#include <stdbool.h>
#include <stdio.h>

#define HAND_IS_EMPTY(game) STACK_IS_EMPTY(&game->hand)
#define WINDOW_IS_EMPTY(game) STACK_IS_EMPTY(&game->window)
#define TABLEAU_IS_EMPTY STACK_IS_EMPTY
#define LAST_FROM_TABLEAU_IS_VISIBLE(tableau)                                  \
  ((tableau)->front != (tableau)->number)

void show_last_from_tableau(game_state_solitary *game, int index) {
  card_stack *current_tableau = &game->tableau[index];
  if (!LAST_FROM_TABLEAU_IS_VISIBLE(current_tableau) &&
      !TABLEAU_IS_EMPTY(current_tableau)) {
    (current_tableau->front)--;
  }
}

void finalize_move(game_state_solitary *game) {
  for (int i = 0; i < 7; i++) {
    show_last_from_tableau(game, i);
  }
}

void change_difficulty(game_state_solitary *game) {
  switch (game->dif) {
  case EASY:
    game->dif = HARD;
    break;
  case HARD:
    game->dif = EASY;
    break;
  }
}

bool new_game(game_state_solitary *game) {
  for (size_t i = 0; i < 4; i++) {
    game->fundation[i] =
        (card_stack){.cards = (game->_fundation[i]), .capacity = 13, 0};
  }
  for (size_t i = 0; i < 7; i++) {
    game->tableau[i] =
        (card_stack){.cards = (game->_tableau[i]), .capacity = 19, 0};
  }
  game->hand = (card_stack){.cards = (game->_hand), .capacity = 13, 0};
  game->stock = (card_stack){.cards = (game->_stock), .capacity = 24, 0};
  game->waste = (card_stack){.cards = (game->_waste), .capacity = 24, 0};
  game->window = (card_stack){.cards = (game->_window), 0};
  switch (game->dif) {
  case EASY:
    game->window.capacity = 1;
    break;
  case HARD:
    game->window.capacity = 3;
    break;
  }

  card_stack deck = INIT_STACK(52);
  new_deck(&deck);
  shuffle(&deck);
  for (size_t r = 0; r < 7; r++) {
    for (size_t t = r; t < 7; t++) {
      card a = ppop(&deck);
      if (push(a, &(game->tableau[t])))
        return false;
      game->tableau[t].front = t;
    }
  }
  for (card a = ppop(&deck); !COMPARE_EQ(INVALID_CARD, a); a = ppop(&deck)) {
    if (push(a, &(game->stock)))
      return false;
  }
  return true;
}

void draw_stock(game_state_solitary *game) {
  for (card iter = qpop(&game->window); !push(iter, &game->waste);
       iter = qpop(&game->window))
    ;
  card a;
  if (COMPARE_EQ(qpeek(&game->stock), INVALID_CARD)) {
    card_stack temp = game->stock;
    game->stock = game->waste;
    game->waste = temp;
  } else {
    for (card iter = qpop(&game->stock); !push(iter, &game->window);
         a = iter = qpop(&game->stock)) {
      ;
    }
    qunpop(a, &game->stock);
  }
}

int can_move_to_fundation(game_state_solitary *game, card c) {
  if (COMPARE_EQ(c, INVALID_CARD))
    return 0;
  card last = ppeek(&game->fundation[c.s]);
  return NEXT_RANK(c, last);
}

int can_move_to_hand(game_state_solitary *game, card c) {
  card in_hand = ppeek(&game->hand);
  return HAND_IS_EMPTY(game) ||
         (DIFFERENT_COLOR(c, in_hand) && NEXT_RANK(c, in_hand));
}

int can_move_to_tableau(game_state_solitary *game, card c, int tableau_index) {
  card_stack *current_tableu = &game->tableau[tableau_index];
  return (((current_tableu->number == 0) && (c.r == K)) ||
          ((LAST_FROM_TABLEAU_IS_VISIBLE(current_tableu)) &&
           (DIFFERENT_COLOR(c, ppeek(current_tableu)) &&
            PREVIOUS_RANK(c, ppeek(current_tableu)))));
}

bool move_window_fundation(game_state_solitary *game) {
  if (can_move_to_fundation(game, qpeek(&game->window))) {
    card a = qpop(&game->window);
    if (WINDOW_IS_EMPTY(game)) {
      push(ppop(&game->waste), &game->window);
    }
    push(a, &game->fundation[a.s]);
    return true;
  }
  return false;
}

bool move_window_tableau(game_state_solitary *game, int tableau_index) {
  if (can_move_to_tableau(game, qpeek(&game->window), tableau_index)) {
    push(qpop(&game->window), &game->tableau[tableau_index]);
    if ((&game->tableau[tableau_index])->number == 1)
      game->tableau[tableau_index].front = 0;
    if (WINDOW_IS_EMPTY(game)) {
      push(ppop(&game->waste), &game->window);
    }
    return true;
  }
  return false;
}

bool move_window_hand(game_state_solitary *game) {
  if (HAND_IS_EMPTY(game)) {
    push(qpop(&game->window), &game->hand);
    if (WINDOW_IS_EMPTY(game)) {
      push(ppop(&game->waste), &game->window);
    }
    return true;
  }
  return false;
}

bool move_hand_tableau(game_state_solitary *game, int tableau_index) {
  if (can_move_to_tableau(game, ppeek(&game->hand), tableau_index)) {
    for (card iter = ppop(&game->hand); !COMPARE_EQ(iter, INVALID_CARD);
         iter = ppop(&game->hand)) {
      push(iter, &game->tableau[tableau_index]);
    }
    finalize_move(game);
    return true;
  }
  return false;
}

bool move_tableau_hand(game_state_solitary *game, int tableau_index) {
  if (can_move_to_hand(game, ppeek(&(game->tableau[tableau_index])))) {
    push(ppop(&(game->tableau[tableau_index])), &game->hand);
    return true;
  }
  return false;
}

bool move_tableau_fundation(game_state_solitary *game, int tableau_index) {
  card_stack *current_tableau = &game->tableau[tableau_index];
  if (can_move_to_fundation(game, ppeek(current_tableau))) {
    card a = ppop(current_tableau);
    if (!LAST_FROM_TABLEAU_IS_VISIBLE(current_tableau) &&
        !TABLEAU_IS_EMPTY(current_tableau)) {
      (current_tableau->front)--;
    }
    push(a, &game->fundation[a.s]);
    return true;
  }
  return false;
}

bool move_tableau_tableau(game_state_solitary *game, int tableau_index1,
                          int tableau_index2) {
  card_stack *tableau1 = &game->tableau[tableau_index1];
  game_state_solitary bkup = *game;
  while (!TABLEAU_IS_EMPTY(tableau1) &&
         LAST_FROM_TABLEAU_IS_VISIBLE(tableau1) &&
         can_move_to_hand(game, ppeek(tableau1))) {
    push(ppop(tableau1), &(game->hand));
    if (can_move_to_tableau(game, ppeek(&(game->hand)), tableau_index2)) {
      return move_hand_tableau(game, tableau_index2);
    }
  }
  *game = bkup;
  return false;
}

bool move_foundation_tableau(game_state_solitary *game, suit fundation_suit,
                             int tableau_index) {
  card_stack *tab = &(game->tableau[tableau_index]);
  card_stack *fun = &(game->fundation[fundation_suit]);
  if (STACK_IS_EMPTY(fun))
    return false;
  if (TABLEAU_IS_EMPTY(tab) && (ppeek(fun).r != K))
    return false;
  card fund = ppeek(&(game->fundation[fundation_suit]));
  if (COMPARE_EQ(fund, INVALID_CARD))
    return false;
  if (can_move_to_tableau(game, fund, tableau_index)) {
    push(ppop(&(game->fundation[fundation_suit])), tab);
    return true;
  }
  return false;
}

bool quick_foundation(game_state_solitary *game) {
  bool control, changed = false;
  do {
    control = false;
    if (move_window_fundation(game) == true) {
      control = true;
      changed = true;
    }
    for (int index = 0; index < 7; index++) {
      if (move_tableau_fundation(game, index) == true) {
        control = true;
        changed = true;
      }
    }
  } while (control);
  return changed;
}

bool quick_tableau(game_state_solitary *game) {
  if (!HAND_IS_EMPTY(game)) {
    for (int index = 0; index < 7; index++) {
      if (move_hand_tableau(game, index)) {
        return true;
      }
    }
    return true;
  }
  for (int index = 0; index < 7; index++) {
    if (move_window_tableau(game, index))
      return true;
  }
  return false;
}

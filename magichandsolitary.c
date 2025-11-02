#include "magichandsolitary.h"
#include "cards.h"
#include <stdbool.h>
#include <stdio.h>

#define HAND_IS_EMPTY(game) COMPARE_EQ(qpeek(&game->hand), INVALID_CARD)
#define WINDOW_IS_EMPTY(game) (game->window.number == 0)
#define TABLEAU_IS_EMPTY(tableau) ((tableau)->number == 0)
#define LAST_FROM_TABLEAU_IS_VISIBLE(tableau)                                 \
  ((tableau)->front != (tableau)->number)

void commit_changes_tableau(game_state_solitary *game) {
  for (int i = 0; i < 7; i++) {
    card_stack *current_tableau = &game->tableau[i];
    if (!LAST_FROM_TABLEAU_IS_VISIBLE(current_tableau) && !TABLEAU_IS_EMPTY(current_tableau)) {
      (current_tableau->front)--;
    }
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
  game->window = (card_stack){.cards = (game->_window), .capacity = 3, 0};

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
  float percentage = 0.0;
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
  card last = ppeek(&game->fundation[c.s]);
  return NEXT_RANK(c, last);
}

int can_move_to_hand(game_state_solitary *game, card c) {
  card in_hand = qpeek(&game->hand);
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
    commit_changes_tableau(game);
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
    if (!LAST_FROM_TABLEAU_IS_VISIBLE(current_tableau) && !TABLEAU_IS_EMPTY(current_tableau)) {
      (current_tableau->front)--;
    }
    push(a, &game->fundation[a.s]);
    return true;
  }
  return false;
}

bool quick_foundation(game_state_solitary *game){
  bool control, changed = false;
  do {
    control = false;
    if(move_window_fundation(game) == true){
      control = true;
      changed = true;
    }
    for(int index = 0; index < 7; index++){
      if(move_tableau_fundation(game,index) == true){
      control = true;
      changed = true;
      }
    }
  } while (control);
  return changed;
}

bool quick_tableau(game_state_solitary *game){
  for(int index = 0; index < 7; index++){
    if(move_window_tableau(game, index))
      return true;
  }
  return false;
}

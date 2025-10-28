#ifndef UI_TERM_H
#define UI_TERM_H

#include <stdio.h>

#include "cards.h"
#include "magichandsolitary.h"

typedef enum {
  NONE,
  EMPTY,
  HIDDEN,
  VISIBLE,
  SELECTED,
  GROUP_SELECTED,
  SIDE_STACKED,
} card_state;

void show_card(card a, card_state state);
void show_side_stack(card_stack *stack);
void show_deck(card_stack *stack);
void show_fundation(card_stack *fundation);
void show_tableau(card_stack *tableau, size_t row);
void show_window(card_stack *window);
void inline show_waste(card_stack *stack) { show_fundation(stack); }
void show_stock(card_stack *stack);
void show_game_state(game_state_solitary *game);

#endif // !UI_TERM_H

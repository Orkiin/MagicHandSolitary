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

void restore();
void setup();
void show_card(card a, card_state state);
void show_side_stack(card_stack *stack);
void show_deck(card_stack *stack);
void show_fundation(card_stack *fundation);
void show_tableau(card_stack *tableau, size_t row);
void show_window(card_stack *window);
void show_stock(card_stack *stack);
void show_hand(card_stack *hand);
void show_game_state(game_state_solitary *game);

#endif // !UI_TERM_H

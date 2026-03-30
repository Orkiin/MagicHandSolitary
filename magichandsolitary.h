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
#ifndef MAGIC_HAND_SOLITARY_GAME
#define MAGIC_HAND_SOLITARY_GAME

#include "cards.h"
#include <stdbool.h>

typedef enum {
  EASY,
  HARD,
} difficulty;

typedef struct {
  union {
    card *buffer;
    struct {
      card _fundation[4][13];
      card _tableau[7][19];
      card _stock[24];
      card _waste[24];
      card _window[3];
      card _hand[13];
    };
  };
  card_stack fundation[4];
  card_stack tableau[7];
  card_stack stock;
  card_stack waste;
  card_stack window;
  card_stack hand;
  difficulty dif;
  bool hand_toggled;
  // TODO: cursor to navigate through the game
} game_state_solitary;

bool new_game(game_state_solitary *game);
void draw_stock(game_state_solitary *game);
bool move_window_fundation(game_state_solitary *game);
bool move_window_tableau(game_state_solitary *game, int tableau_index);
bool move_window_hand(game_state_solitary *game);
bool move_hand_tableau(game_state_solitary *game, int tableau_index);
bool move_tableau_hand(game_state_solitary *game, int tableau_index);
bool move_tableau_fundation(game_state_solitary *game, int tableau_index);
bool move_tableau_tableau(game_state_solitary *game, int tableau_index1,
                          int tableau_index2);
bool move_foundation_tableau(game_state_solitary *game, suit fundation_suit,
                             int tableau_index);
bool quick_foundation(game_state_solitary *game);
bool quick_tableau(game_state_solitary *game);

#endif // !MAGIC_HAND_SOLITARY_GAME

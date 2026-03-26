#ifndef MAGIC_HAND_SOLITARY_GAME
#define MAGIC_HAND_SOLITARY_GAME

#include "cards.h"
#include <stdbool.h>

typedef struct {
  card _fundation[4][13];
  card_stack fundation[4];
  card _tableau[7][19];
  card_stack tableau[7];
  card _stock[24];
  card_stack stock;
  card _waste[24];
  card_stack waste;
  card _window[3];
  card_stack window;
  card _hand[13];
  card_stack hand;
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
bool move_tableau_tableau(game_state_solitary *game, int tableau_index1, int tableau_index2);
bool quick_foundation(game_state_solitary *game);
bool quick_tableau(game_state_solitary *game);

#endif // !MAGIC_HAND_SOLITARY_GAME

#ifndef MAGIC_HAND_SOLITARY_GAME
#define MAGIC_HAND_SOLITARY_GAME

#include "cards.h"

typedef struct {
  card _fundation_hand[5][13];
  card_stack fundation[4];
  card _tableau[7][19];
  card_stack tableau[7];
  card _waste_stock[24];
  card_stack waste_stock;
  card _window[3];
  card_stack window;
  card_stack hand;
  // TODO: cursor to navigate through the game
} game_state_solitary;

int new_game(game_state_solitary *game);

#endif // !MAGIC_HAND_SOLITARY_GAME

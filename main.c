#include <stdio.h>

#include "cards.h"
#include "magichandsolitary.h"
#include "uiterm.h"

int main(void) {
  game_state_solitary game = {0};
  new_game(&game);
  show_game_state(&game);
  push(qpop(&(game.waste_stock)),&(game.window));
  push(qpop(&(game.waste_stock)),&(game.window));
  push(qpop(&(game.waste_stock)),&(game.window));
  show_game_state(&game);
  push(qpop(&(game.window)),&(game.hand));
  show_game_state(&game);
  qunpop(ppop(&(game.tableau[3])),&(game.hand));
  show_game_state(&game);
  return EXIT_SUCCESS;
}

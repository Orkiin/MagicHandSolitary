#include "cards.h"
#include "magichandsolitary.h"
#include "uiterm.h"
#include <stdlib.h>

int main(void) {
  game_state_solitary game = {0};
  new_game(&game);
  show_game_state(&game);
  for (int i = 0; i < 15; i++) {
    draw_stock(&game);
    show_game_state(&game);
    while(move_window_fundation(&game)){
      show_game_state(&game);
    }
    for (int j = 0; j < 0; j++) {
      bool moved = move_tableau_fundation(&game, j);
      if(moved)
      show_game_state(&game);
    }
    if (rand() % 100 < 50){
      if(move_window_hand(&game));
      else {
        push(qpop(&game.window),&game.hand);
      }
      show_game_state(&game);
    }
  }
  return EXIT_SUCCESS;
}

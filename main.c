#include "cards.h"
#include "magichandsolitary.h"
#include "uiterm.h"
#include <stdlib.h>

int main(void) {
  game_state_solitary game = {0};
  new_game(&game);
  show_game_state(&game);
  for (int i = 0; i < 12; i++) {
    draw_stock(&game);
    show_game_state(&game);
    move_window_fundation(&game);
    if (rand() % 100 < 50)
      move_window_hand(&game);
  }
  show_game_state(&game);
  return EXIT_SUCCESS;
}

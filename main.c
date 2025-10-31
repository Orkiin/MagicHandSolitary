#include "magichandsolitary.h"
#include "uiterm.h"
#include <stdlib.h>
#include <unistd.h>

typedef enum {
  EXIT = -1,
  UNDEFINED,
} key_pressed;

key_pressed get_key() {
  char c;
  read(STDIN_FILENO, &c, 1);
  switch (c) {
  case 'q':
  case 'Q':
    return EXIT;
  default:
    return UNDEFINED;
  }
}

int main(void) {
  setup();
  game_state_solitary game = {0};
  new_game(&game);
  show_game_state(&game);
  if (get_key() == EXIT) {
    return EXIT_SUCCESS;
  }
  while (true) {
    draw_stock(&game);
    show_game_state(&game);
    if (get_key() == EXIT) {
      return EXIT_SUCCESS;
    }
    while (move_window_fundation(&game) == true) {
      show_game_state(&game);
      if (get_key() == EXIT) {
        return EXIT_SUCCESS;
      }
    }
    int changed = 0;
  TRY_AGAIN:
    for (int j = 0; j < 7; j++) {
      if (move_tableau_fundation(&game, j)) {
        show_game_state(&game);
        if (get_key() == EXIT) {
          return EXIT_SUCCESS;
        }
      }
    }
    for (int j = 0; j < 7; j++) {
      if (move_window_tableau(&game, j)) {
        show_game_state(&game);
        if (get_key() == EXIT) {
          return EXIT_SUCCESS;
        }
        j = 0;
        changed = 1;
      }
    }
    if (changed) {
      changed = 0;
      goto TRY_AGAIN;
    }
  }
  return EXIT_SUCCESS;
}

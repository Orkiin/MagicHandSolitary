#include "menu.h"

void menu(game_state_solitary *game) {
  while (true) {
    show_menu();
    game->hand_toggled = true;
    switch (get_keypressed()) {
    case TABLEAU1:
      game->dif = EASY;
      return;
    case TABLEAU2:
      game->dif = HARD;
      return;
    case ARROW_U:
    case ARROW_D:
    case ARROW_L:
    case ARROW_R:
      printf("\n\n'Pressed arrows?'");
      fflush(stdout);
      get_keypressed();
      break;
    case ENTER:
      printf("\n\n'Pressed enter?'");
      fflush(stdout);
      get_keypressed();
      break;
    case UNDEFINED:
      printf("\n\n'Pressed Undefined key'");
      fflush(stdout);
      get_keypressed();
      break;
    case EXIT:
      exit(EXIT_SUCCESS);
    }
  }
}

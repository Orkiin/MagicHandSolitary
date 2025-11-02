#include "inputcontrols.h"
#include "magichandsolitary.h"
#include "uiterm.h"
#include <stdlib.h>

int main(void) {
  setup();
  game_state_solitary game = {0};
  new_game(&game);
  show_game_state(&game);
  for (key_pressed key = get_keypressed(); key != EXIT;
       key = get_keypressed()) {
    switch (key) {
    case DRAW:
      draw_stock(&game);
      show_game_state(&game);
      break;
    case RESET:
      new_game(&game);
      show_game_state(&game);
      break;
    case FUNDATION1:
    case FUNDATION2:
    case FUNDATION3:
    case FUNDATION4:
      quick_fundation(&game);
      show_game_state(&game);
      break;
    case QUICKTABLEAU:
      quick_tableau(&game);
      show_game_state(&game);
      break;
    case WINDOW:
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        move_window_fundation(&game);
        show_game_state(&game);
        break;
      case TABLEAU1:
        move_window_tableau(&game, 0);
        show_game_state(&game);
        break;
      case TABLEAU2:
        move_window_tableau(&game, 1);
        show_game_state(&game);
        break;
      case TABLEAU3:
        move_window_tableau(&game, 2);
        show_game_state(&game);
        break;
      case TABLEAU4:
        move_window_tableau(&game, 3);
        show_game_state(&game);
        break;
      case TABLEAU5:
        move_window_tableau(&game, 4);
        show_game_state(&game);
        break;
      case TABLEAU6:
        move_window_tableau(&game, 5);
        show_game_state(&game);
        break;
      case TABLEAU7:
        move_window_tableau(&game, 6);
        show_game_state(&game);
        break;
      default:
        break;
      }
      break;
    case TABLEAU1:
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        move_tableau_fundation(&game, 0);
        show_game_state(&game);
        break;
      case HAND:
        move_tableau_hand(&game, 0);
        show_game_state(&game);
        break;
      default:
        break;
      }
      break;
    case TABLEAU2:
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        move_tableau_fundation(&game, 1);
        show_game_state(&game);
        break;
      case HAND:
        move_tableau_hand(&game, 1);
        show_game_state(&game);
        break;
      default:
        break;
      }
      break;
    case TABLEAU3:
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        move_tableau_fundation(&game, 2);
        show_game_state(&game);
        break;
      case HAND:
        move_tableau_hand(&game, 2);
        show_game_state(&game);
        break;
      default:
        break;
      }
      break;
    case TABLEAU4:
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        move_tableau_fundation(&game, 3);
        show_game_state(&game);
        break;
      case HAND:
        move_tableau_hand(&game, 3);
        show_game_state(&game);
        break;
      default:
        break;
      }
      break;
    case TABLEAU5:
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        move_tableau_fundation(&game, 4);
        show_game_state(&game);
        break;
      case HAND:
        move_tableau_hand(&game, 4);
        show_game_state(&game);
        break;
      default:
        break;
      }
      break;
    case TABLEAU6:
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        move_tableau_fundation(&game, 5);
        show_game_state(&game);
        break;
      case HAND:
        move_tableau_hand(&game, 5);
        show_game_state(&game);
        break;
      default:
        break;
      }
      break;
    case TABLEAU7:
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        move_tableau_fundation(&game, 6);
        show_game_state(&game);
        break;
      case HAND:
        move_tableau_hand(&game, 6);
        show_game_state(&game);
        break;
      default:
        break;
      }
      break;
    default:
      continue;
    }
  }
  return EXIT_SUCCESS;
}

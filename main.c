#include "generalcontainer.h"
#include "inputcontrols.h"
#include "magichandsolitary.h"
#include "uiterm.h"
#include <stdlib.h>

TEMPLATEGENERALCONTAINER(game_state_solitary);
TEMPLATERESULTERRORAWARE(game_state_solitary);
TEMPLATEOPTION(game_state_solitary);
TEMPLATEPUSHEND(game_state_solitary)
TEMPLATEPUSHEND_OPT(game_state_solitary)
TEMPLATESTACKPOP(game_state_solitary)
TEMPLATESTACKPOP_OPT(game_state_solitary)
TEMPLATESTACKPOP_UNSAFE(game_state_solitary)
TEMPLATESTACKPEEK(game_state_solitary)
TEMPLATESTACKPEEK_OPT(game_state_solitary)
TEMPLATESTACKPEEK_UNSAFE(game_state_solitary)
TEMPLATEQUEUEPOP(game_state_solitary)
TEMPLATEQUEUEPOP_OPT(game_state_solitary)

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
      switch(get_keypressed()){
        case TABLEAU1:
          move_foundation_tableau(&game,0);
          show_game_state(&game);
          break;
        case TABLEAU2:
          move_foundation_tableau(&game,1);
          show_game_state(&game);
          break;
        case TABLEAU3:
          move_foundation_tableau(&game,2);
          show_game_state(&game);
          break;
        case TABLEAU4:
          move_foundation_tableau(&game,3);
          show_game_state(&game);
          break;
        case TABLEAU5:
          move_foundation_tableau(&game,4);
          show_game_state(&game);
          break;
        case TABLEAU6:
          move_foundation_tableau(&game,5);
          show_game_state(&game);
          break;
        case TABLEAU7:
          move_foundation_tableau(&game,6);
          show_game_state(&game);
          break;
        case FUNDATION1:
        case FUNDATION2:
        case FUNDATION3:
        case FUNDATION4:
          quick_foundation(&game);
          show_game_state(&game);
          break;
        default:
          break;
      }
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
      case TABLEAU2:
        move_tableau_tableau(&game,0,1);
        show_game_state(&game);
        break;
      case TABLEAU3:
        move_tableau_tableau(&game,0,2);
        show_game_state(&game);
        break;
      case TABLEAU4:
        move_tableau_tableau(&game,0,3);
        show_game_state(&game);
        break;
      case TABLEAU5:
        move_tableau_tableau(&game,0,4);
        show_game_state(&game);
        break;
      case TABLEAU6:
        move_tableau_tableau(&game,0,5);
        show_game_state(&game);
        break;
      case TABLEAU7:
        move_tableau_tableau(&game,0,6);
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
      case TABLEAU1:
        move_tableau_tableau(&game,1,0);
        show_game_state(&game);
        break;
      case TABLEAU3:
        move_tableau_tableau(&game,1,2);
        show_game_state(&game);
        break;
      case TABLEAU4:
        move_tableau_tableau(&game,1,3);
        show_game_state(&game);
        break;
      case TABLEAU5:
        move_tableau_tableau(&game,1,4);
        show_game_state(&game);
        break;
      case TABLEAU6:
        move_tableau_tableau(&game,1,5);
        show_game_state(&game);
        break;
      case TABLEAU7:
        move_tableau_tableau(&game,1,6);
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
      case TABLEAU1:
        move_tableau_tableau(&game,2,0);
        show_game_state(&game);
        break;
      case TABLEAU2:
        move_tableau_tableau(&game,2,1);
        show_game_state(&game);
        break;
      case TABLEAU4:
        move_tableau_tableau(&game,2,3);
        show_game_state(&game);
        break;
      case TABLEAU5:
        move_tableau_tableau(&game,2,4);
        show_game_state(&game);
        break;
      case TABLEAU6:
        move_tableau_tableau(&game,2,5);
        show_game_state(&game);
        break;
      case TABLEAU7:
        move_tableau_tableau(&game,2,6);
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
      case TABLEAU1:
        move_tableau_tableau(&game,3,0);
        show_game_state(&game);
        break;
      case TABLEAU2:
        move_tableau_tableau(&game,3,1);
        show_game_state(&game);
        break;
      case TABLEAU3:
        move_tableau_tableau(&game,3,2);
        show_game_state(&game);
        break;
      case TABLEAU5:
        move_tableau_tableau(&game,3,4);
        show_game_state(&game);
        break;
      case TABLEAU6:
        move_tableau_tableau(&game,3,5);
        show_game_state(&game);
        break;
      case TABLEAU7:
        move_tableau_tableau(&game,3,6);
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
      case TABLEAU1:
        move_tableau_tableau(&game,4,0);
        show_game_state(&game);
        break;
      case TABLEAU2:
        move_tableau_tableau(&game,4,1);
        show_game_state(&game);
        break;
      case TABLEAU3:
        move_tableau_tableau(&game,4,2);
        show_game_state(&game);
        break;
      case TABLEAU4:
        move_tableau_tableau(&game,4,3);
        show_game_state(&game);
        break;
      case TABLEAU6:
        move_tableau_tableau(&game,4,5);
        show_game_state(&game);
        break;
      case TABLEAU7:
        move_tableau_tableau(&game,4,6);
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
      case TABLEAU1:
        move_tableau_tableau(&game,5,0);
        show_game_state(&game);
        break;
      case TABLEAU2:
        move_tableau_tableau(&game,5,1);
        show_game_state(&game);
        break;
      case TABLEAU3:
        move_tableau_tableau(&game,5,2);
        show_game_state(&game);
        break;
      case TABLEAU4:
        move_tableau_tableau(&game,5,3);
        show_game_state(&game);
        break;
      case TABLEAU5:
        move_tableau_tableau(&game,5,4);
        show_game_state(&game);
        break;
      case TABLEAU7:
        move_tableau_tableau(&game,5,6);
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
      case TABLEAU1:
        move_tableau_tableau(&game,6,0);
        show_game_state(&game);
        break;
      case TABLEAU2:
        move_tableau_tableau(&game,6,1);
        show_game_state(&game);
        break;
      case TABLEAU3:
        move_tableau_tableau(&game,6,2);
        show_game_state(&game);
        break;
      case TABLEAU4:
        move_tableau_tableau(&game,6,3);
        show_game_state(&game);
        break;
      case TABLEAU5:
        move_tableau_tableau(&game,6,4);
        show_game_state(&game);
        break;
      case TABLEAU6:
        move_tableau_tableau(&game,6,5);
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

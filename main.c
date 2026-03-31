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
#include "generalcontainer.h"
#include "inputcontrols.h"
#include "magichandsolitary.h"
#include "menu.h"
#include "uiterm.h"
#include <stdlib.h>

#define MAX_UNDO_STACK 20

TEMPLATEGENERALCONTAINER(game_state_solitary);
TEMPLATEPUSHEND(game_state_solitary);
TEMPLATESTACKPOP_UNSAFE(game_state_solitary);
TEMPLATERESULTERRORAWARE(game_state_solitary);
TEMPLATESTACKPOP(game_state_solitary);

bool run_game(game_state_solitary *game);
bool application(menu_t *menu);

int main(void) {
  setup();
  menu_t main_menu = (menu_t){
      .option =
          (menu_option[4]){
              (menu_option){get_text(LANG_ES, NEW_GAME_CLASSIC),
                            NEW_GAME_CLASSIC},
              (menu_option){get_text(LANG_ES, NEW_GAME_MAGICHAND),
                            NEW_GAME_MAGICHAND},
              (menu_option){get_text(LANG_ES, CHANGE_DIFFICULTY),
                            CHANGE_DIFFICULTY},
              (menu_option){get_text(LANG_ES, EXIT_GAME), EXIT_GAME},
          },
      .game = (game_state_solitary[1]){0},
      .options_number = 4,
      .current_index = 0,
  };
  return application(&main_menu);
}

bool application(menu_t *menu) {
  while (true) {
    show_menu(menu);
    switch (get_keypressed()) {
    case ARROW_D:
      menu_next_option(menu);
      break;
    case ARROW_U:
      menu_prev_option(menu);
      break;
    case ENTER:
    case ARROW_R:
      if (menu_select(menu))
        while (run_game(menu->game))
          ;
    }
  }
  return EXIT_SUCCESS;
}

bool run_game(game_state_solitary *game) {
  new_game(game);
  show_game_state(game);
  game_state_solitary_container hand_undo = (game_state_solitary_container){
      .data = (game_state_solitary[1]){0}, .capacity = 1, 0};
  game_state_solitary_container undo_stack = (game_state_solitary_container){
      .data = (game_state_solitary[MAX_UNDO_STACK]){0},
      .capacity = MAX_UNDO_STACK,
      0};
  result_game_state_solitary can_undo;
  for (key_pressed key = get_keypressed(); key != EXIT;
       key = get_keypressed()) {
    switch (key) {
    case DRAW:
      push_game_state_solitary(*game, &undo_stack);
      draw_stock(game);
      show_game_state(game);
      break;
    case RESET:
      return true;
      break;
    case HAND:
      if (!game->hand_toggled)
        break;
      push_game_state_solitary(*game, &undo_stack);
      push_game_state_solitary(*game, &hand_undo);
      while (true) {
        switch (get_keypressed()) {
        case TABLEAU1:
          move_tableau_hand(game, 0);
          show_game_state(game);
          break;
        case TABLEAU2:
          move_tableau_hand(game, 1);
          show_game_state(game);
          break;
        case TABLEAU3:
          move_tableau_hand(game, 2);
          show_game_state(game);
          break;
        case TABLEAU4:
          move_tableau_hand(game, 3);
          show_game_state(game);
          break;
        case TABLEAU5:
          move_tableau_hand(game, 4);
          show_game_state(game);
          break;
        case TABLEAU6:
          move_tableau_hand(game, 5);
          show_game_state(game);
          break;
        case TABLEAU7:
          move_tableau_hand(game, 6);
          show_game_state(game);
          break;
        case QUICKTABLEAU:
          quick_tableau(game);
          show_game_state(game);
          goto FINALIZE_HAND;
          break;
        default:
          goto UNDO_HAND;
          break;
        }
      }
    UNDO_HAND:
      // restaura estado del juego antes de mano;
      *game = ppop_game_state_solitary_unsafe(&hand_undo);
      ppop_game_state_solitary_unsafe(&undo_stack);
    FINALIZE_HAND:
      show_game_state(game);
      break;
    case FUNDATION1:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case TABLEAU1:
        if (move_foundation_tableau(game, 0, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_foundation_tableau(game, 0, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_foundation_tableau(game, 0, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_foundation_tableau(game, 0, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_foundation_tableau(game, 0, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_foundation_tableau(game, 0, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_foundation_tableau(game, 0, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case FUNDATION2:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case TABLEAU1:
        if (move_foundation_tableau(game, 1, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_foundation_tableau(game, 1, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_foundation_tableau(game, 1, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_foundation_tableau(game, 1, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_foundation_tableau(game, 1, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_foundation_tableau(game, 1, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_foundation_tableau(game, 1, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case FUNDATION3:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case TABLEAU1:
        if (move_foundation_tableau(game, 2, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_foundation_tableau(game, 2, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_foundation_tableau(game, 2, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_foundation_tableau(game, 2, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_foundation_tableau(game, 2, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_foundation_tableau(game, 2, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_foundation_tableau(game, 2, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case FUNDATION4:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case TABLEAU1:
        if (move_foundation_tableau(game, 3, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_foundation_tableau(game, 3, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_foundation_tableau(game, 3, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_foundation_tableau(game, 3, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_foundation_tableau(game, 3, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_foundation_tableau(game, 3, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_foundation_tableau(game, 3, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case QUICKFUNDATION:
      push_game_state_solitary(*game, &undo_stack);
      if (quick_foundation(game)) {
        show_game_state(game);
        break;
      }
      ppop_game_state_solitary_unsafe(&undo_stack);
      break;
    case QUICKTABLEAU:
      push_game_state_solitary(*game, &undo_stack);
      if (quick_tableau(game)) {
        show_game_state(game);
        break;
      }
      ppop_game_state_solitary_unsafe(&undo_stack);
      break;
    case WINDOW:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        if (move_window_fundation(game)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU1:
        if (move_window_tableau(game, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_window_tableau(game, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_window_tableau(game, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_window_tableau(game, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_window_tableau(game, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_window_tableau(game, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_window_tableau(game, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case TABLEAU1:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        if (move_tableau_fundation(game, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_tableau_tableau(game, 0, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_tableau_tableau(game, 0, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_tableau_tableau(game, 0, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_tableau_tableau(game, 0, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_tableau_tableau(game, 0, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_tableau_tableau(game, 0, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case TABLEAU2:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        if (move_tableau_fundation(game, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU1:
        if (move_tableau_tableau(game, 1, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_tableau_tableau(game, 1, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_tableau_tableau(game, 1, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_tableau_tableau(game, 1, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_tableau_tableau(game, 1, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_tableau_tableau(game, 1, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case TABLEAU3:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        if (move_tableau_fundation(game, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU1:
        if (move_tableau_tableau(game, 2, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_tableau_tableau(game, 2, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_tableau_tableau(game, 2, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_tableau_tableau(game, 2, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_tableau_tableau(game, 2, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_tableau_tableau(game, 2, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case TABLEAU4:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        if (move_tableau_fundation(game, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU1:
        if (move_tableau_tableau(game, 3, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_tableau_tableau(game, 3, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_tableau_tableau(game, 3, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_tableau_tableau(game, 3, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_tableau_tableau(game, 3, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_tableau_tableau(game, 3, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case TABLEAU5:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        if (move_tableau_fundation(game, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU1:
        if (move_tableau_tableau(game, 4, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_tableau_tableau(game, 4, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_tableau_tableau(game, 4, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_tableau_tableau(game, 4, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_tableau_tableau(game, 4, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_tableau_tableau(game, 4, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case TABLEAU6:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        if (move_tableau_fundation(game, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU1:
        if (move_tableau_tableau(game, 5, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_tableau_tableau(game, 5, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_tableau_tableau(game, 5, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_tableau_tableau(game, 5, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_tableau_tableau(game, 5, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU7:
        if (move_tableau_tableau(game, 5, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case TABLEAU7:
      push_game_state_solitary(*game, &undo_stack);
      switch (get_keypressed()) {
      case FUNDATION1:
      case FUNDATION2:
      case FUNDATION3:
      case FUNDATION4:
        if (move_tableau_fundation(game, 6)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU1:
        if (move_tableau_tableau(game, 6, 0)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU2:
        if (move_tableau_tableau(game, 6, 1)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU3:
        if (move_tableau_tableau(game, 6, 2)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU4:
        if (move_tableau_tableau(game, 6, 3)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU5:
        if (move_tableau_tableau(game, 6, 4)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      case TABLEAU6:
        if (move_tableau_tableau(game, 6, 5)) {
          show_game_state(game);
          break;
        }
        ppop_game_state_solitary_unsafe(&undo_stack);
        break;
      default:
        break;
      }
      break;
    case UNDO:
      can_undo = ppop_game_state_solitary(&undo_stack);
      switch (can_undo.r) {
      case OK:
        *game = can_undo.data.t;
        show_game_state(game);
        break;
      default:
        // report error
        break;
      }
      break;
    default:
      continue;
    }
    int i;
    for (i = 0; i < 7; i++) {
      if (!STACK_IS_EMPTY(&(game->tableau[i])))
        break;
    }
    if (i == 7 && STACK_IS_EMPTY(&(game->stock)) &&
        STACK_IS_EMPTY(&(game->waste))) {
      printf("YOU WON! Press 'N' to play a new game, any key to exit");
      fflush(stdout);
      if (get_keypressed() == RESET) {
        return true;
      }
      return false;
    }
  }
  return false;
}

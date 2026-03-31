#include "menu.h"

const char *texts[LANG_COUNT][OPTIONS_COUNT] = {
    [LANG_ES] =
        {
            [NEW_GAME_CLASSIC] = "Jugar Clasico",
            [NEW_GAME_MAGICHAND] = "Jugar Mano Magica",
            [CHANGE_DIFFICULTY] = "Cambiar Dificultad",
            [EXIT_GAME] = "Salir del Juego",
        },
    [LANG_EN] =
        {
            [NEW_GAME_CLASSIC] = "Play Classic Game",
            [NEW_GAME_MAGICHAND] = "Play MagicHand Game",
            [CHANGE_DIFFICULTY] = "Change Difficulty",
            [EXIT_GAME] = "Exit Game",
        },
};

const char *get_text(LANG_ID lan, options opt) { return texts[lan][opt]; }

void menu_next_option(menu_t *menu) {
  menu->current_index++;
  if (menu->options_number == menu->current_index) {
    menu->current_index = 0;
  }
}

void menu_prev_option(menu_t *menu) {
  if (0 == menu->current_index) {
    menu->current_index = menu->options_number - 1;
  } else {
    menu->current_index--;
  }
}

bool menu_select(menu_t *menu) {
  switch (menu->option[menu->current_index].option) {
  case NEW_GAME_CLASSIC:
    menu->game->hand_toggled = false;
    return true;
  case NEW_GAME_MAGICHAND:
    menu->game->hand_toggled = true;
    return true;
  case CHANGE_DIFFICULTY:
    change_difficulty(menu->game);
    return false;
  case EXIT_GAME:
    exit(EXIT_SUCCESS);
  }
  return false;
}

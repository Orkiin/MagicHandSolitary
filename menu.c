#include "menu.h"

const char *texts[LANG_COUNT][OPTIONS_COUNT] = {
    [LANG_ES] =
        {
            [NEW_GAME_CLASSIC] = "Jugar Clasico",
            [NEW_GAME_MAGICHAND] = "Jugar Mano Magica",
            [CONFIGURE] = "Configuracion",
            [CHANGE_LANGUAGE] = "Espanol",
            [HELP] = "Ayuda",
            [BACK] = "Volver",
            [CHANGE_DIFFICULTY] = "Cambiar Dificultad",
            [EXIT_GAME] = "Salir del Juego",
        },
    [LANG_EN] =
        {
            [NEW_GAME_CLASSIC] = "Play Classic Game",
            [NEW_GAME_MAGICHAND] = "Play MagicHand Game",
            [CHANGE_DIFFICULTY] = "Change Difficulty",
            [CHANGE_LANGUAGE] = "English",
            [EXIT_GAME] = "Exit Game",
        },
};

const char *get_text(LANG_ID lan, options opt) { return texts[lan][opt]; }

void change_lang(menu_t *menu, LANG_ID desired) {
  LANG_ID def = LANG_ES;
  for (int i = 0; i < menu->options_number; i++) {
    const char *text = get_text(desired, menu->option[i].option);
    if (text == NULL) {
      menu->option[i].option_text = get_text(def, menu->option[i].option);
      continue;
    }
    menu->option[i].option_text = text;
  }
}

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
  static LANG_ID current = LANG_ES;
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
  case CHANGE_LANGUAGE:
    current++;
    if (current == LANG_COUNT) {
      current = 0;
    }
    change_lang(menu, current);
    return false;
  case EXIT_GAME:
    exit(EXIT_SUCCESS);
  }
  return false;
}

menu_t create_menu(options *options) {
  int cnt = 0;
  for (; (options[cnt]) != OPTIONS_COUNT; cnt++)
    ;
  menu_t menu = {
      .option = malloc(sizeof(menu_option) * cnt),
      .game = calloc(sizeof(game_state_solitary), 1),
      .options_number = cnt,
      .current_index = 0,
  };
  for (int i = 0; i < cnt; i++) {
    menu.option[i].option_text = get_text(LANG_ES, options[i]);
    menu.option[i].option = options[i];
  }
  return menu;
}

void destroy_menu(menu_t *menu) {
  free(menu->option);
  free(menu->game);
}

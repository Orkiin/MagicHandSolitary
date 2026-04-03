#include "menu.h"
/*
  NEW_GAME_CLASSIC,
  NEW_GAME_MAGICHAND,
  CONFIGURE,
  CHANGE_DIFFICULTY,
  CHANGE_LANGUAGE,
  HELP,
  BACK,
  EXIT_GAME,
  OPTIONS_COUNT,
 */

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
            [HELP] = "Help",
            [BACK] = "Back",
            [CONFIGURE] = "Configuration",
            [EXIT_GAME] = "Exit Game",
        },
};

const char *get_text(LANG_ID lan, options opt) { return texts[lan][opt]; }

void update_menu_text(menu_t *menu) {
  for (int i = 0; i < menu->options_number; i++) {
    const char *text = get_text(menu->lang, menu->option[i].option);
    if (text == NULL) {
      menu->option[i].option_text = get_text(LANG_ES, menu->option[i].option);
      continue;
    }
    menu->option[i].option_text = text;
  }
}

void change_lang(menu_t *menu) {
  menu->lang++;
  if (menu->lang == LANG_COUNT)
    menu->lang = 0;
  update_menu_text(menu);
  if (menu->parent != NULL) {
    change_lang(menu->parent);
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

menu_t create_menu(options *options) {
  int cnt = 0;
  for (; (options[cnt]) != OPTIONS_COUNT; cnt++)
    ;
  menu_t menu = {
      .parent = NULL,
      .lang = LANG_ES,
      .option = malloc(sizeof(menu_option) * cnt),
      .game = calloc(sizeof(game_state_solitary), 1),
      .options_number = cnt,
      .current_index = 0,
  };
  for (int i = 0; i < cnt; i++) {
    menu.option[i].option_text = get_text(menu.lang, options[i]);
    menu.option[i].option = options[i];
  }
  return menu;
}

menu_t *create_submenu(menu_t *parent, options *options) {
  int cnt = 0;
  for (; (options[cnt]) != OPTIONS_COUNT; cnt++)
    ;
  menu_t *menu = malloc(sizeof(menu_t));
  *menu = (menu_t){
      .parent = parent,
      .lang = parent->lang,
      .option = malloc(sizeof(menu_option) * cnt),
      .game = parent->game,
      .options_number = cnt,
      .current_index = 0,
  };
  for (int i = 0; i < cnt; i++) {
    menu->option[i].option = options[i];
  }
  update_menu_text(menu);
  return menu;
}

void destroy_menu(menu_t *menu) {
  free(menu->option);
  if (menu->parent != NULL) {
    free(menu);
    return;
  }
  free(menu->game);
}

bool menu_select(menu_t **menu_in) {
  menu_t *menu = *menu_in;
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
    change_lang(menu);
    return false;
  case HELP:
    return false;
  case CONFIGURE:
    *menu_in =
        create_submenu(menu, (options[4]){CHANGE_DIFFICULTY, CHANGE_LANGUAGE,
                                          BACK, OPTIONS_COUNT});
    return false;
  case BACK:
  case EXIT_GAME:
    if (menu->parent != NULL) {
      *menu_in = menu->parent;
      destroy_menu(menu);
      return false;
    }
    destroy_menu(menu);
    exit(EXIT_SUCCESS);
  }
  return false;
}

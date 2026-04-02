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
#ifndef CARDS_MENU_H
#define CARDS_MENU_H

#include "inputcontrols.h"
#include "magichandsolitary.h"
#include <stdio.h>

typedef enum {
  NEW_GAME_CLASSIC,
  NEW_GAME_MAGICHAND,
  CONFIGURE,
  CHANGE_DIFFICULTY,
  CHANGE_LANGUAGE,
  HELP,
  BACK,
  EXIT_GAME,
  OPTIONS_COUNT,
} options;

typedef enum {
  LANG_EN,
  LANG_ES,
  LANG_COUNT,
} LANG_ID;

typedef struct {
  const char *option_text;
  options option;
} menu_option;

typedef struct {
  menu_option *option;
  game_state_solitary *game;
  size_t options_number;
  size_t current_index;
} menu_t;

const char *get_text(LANG_ID lan, options opt);
void change_lang(menu_t *menu, LANG_ID desired);
void menu_next_option(menu_t *menu);
void menu_prev_option(menu_t *menu);
bool menu_select(menu_t *menu);
// OPTIONS_COUNT terminated array of options
menu_t create_menu(options *options);
void destroy_menu(menu_t *menu);

#endif // CARDS_MENU_H

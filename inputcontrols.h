#ifndef INPUT_CONTROL_H
#define INPUT_CONTROL_H

#include <unistd.h>

typedef enum {
  UNDEFINED = -2,
  EXIT = -1,
  UNDO,
  RESET,
  HAND,
  DRAW,
  WINDOW,
  FUNDATION1,
  FUNDATION2,
  FUNDATION3,
  FUNDATION4,
  QUICKTABLEAU,
  TABLEAU1,
  TABLEAU2,
  TABLEAU3,
  TABLEAU4,
  TABLEAU5,
  TABLEAU6,
  TABLEAU7,
} key_pressed;

key_pressed get_keypressed();

#endif // INPUT_CONTROL_H

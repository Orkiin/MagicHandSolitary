#include "inputcontrols.h"

key_pressed get_keypressed() {
  char c;
  read(STDIN_FILENO, &c, 1);
  switch (c) {
  case 'q':
  case 'Q':
    return EXIT;
  case 'n':
  case 'N':
    return RESET;
  case ' ':
    return DRAW;
  case 'w':
  case 'W':
    return WINDOW;
  case 'f':
  case 'F':
    return QUICKFUNDATION;
  case 'z':
  case 'Z':
    return FUNDATION1;
  case 'x':
  case 'X':
    return FUNDATION2;
  case 'c':
  case 'C':
    return FUNDATION3;
  case 'v':
  case 'V':
    return FUNDATION4;
  case 't':
  case 'T':
    return QUICKTABLEAU;
  case '1':
    return TABLEAU1;
  case '2':
    return TABLEAU2;
  case '3':
    return TABLEAU3;
  case '4':
    return TABLEAU4;
  case '5':
    return TABLEAU5;
  case '6':
    return TABLEAU6;
  case '7':
    return TABLEAU7;
  case 'U':
  case 'u':
    return UNDO;
  default:
    return UNDEFINED;
  }
}

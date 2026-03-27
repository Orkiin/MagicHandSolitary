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

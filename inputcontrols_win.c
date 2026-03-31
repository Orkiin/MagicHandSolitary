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
#if defined(WINDOWS)
#include <conio.h>

#define ESCAPED_INPUT 224

int kbread(int *c, int len) {
  for(int i = 0; i < len; i++){
    if(!_kbhit()){
        return i;
    }
    c[i] = _getch();
  }
  return len;
}

#define READ(FILENO, chrptr, chrlen) do{} while(!kbread(chrptr, chrlen)) 

#else
#define ESCAPED_INPUT 0x1b
#define READ(FILENO, chrptr, chrlen) read(FILENO, chrptr, chrlen)
#endif // defined


key_pressed escaped_input() {
  int c[5];
  READ(STDIN_FILENO, c, 5);
  switch (c[0]) {
  case '[':
    switch (c[1]) {
    case 'A':
      return ARROW_U;
    case 'B':
      return ARROW_D;
    case 'C':
      return ARROW_R;
    case 'D':
      return ARROW_L;
    }
    case 'H':
      return ARROW_U;
    case 'P':
      return ARROW_D;
    case 'K':
      return ARROW_L;
    case 'M':
      return ARROW_R;
  }
  return UNDEFINED;
}

key_pressed get_keypressed() {
  int c;
  READ(STDIN_FILENO, &c, 1);
  switch (c) {
  case 10:
  case 13:
    return ENTER;
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
  case 'H':
  case 'h':
    return HAND;
  case ESCAPED_INPUT:
    return escaped_input();
  default:
    return UNDEFINED;
  }
}

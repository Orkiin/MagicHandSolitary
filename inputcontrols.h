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
  QUICKFUNDATION,
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
  ARROW_D,
  ARROW_U,
  ARROW_L,
  ARROW_R,
  ENTER,
} key_pressed;

key_pressed get_keypressed();

#endif // INPUT_CONTROL_H

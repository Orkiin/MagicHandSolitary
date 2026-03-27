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
#ifndef CARDS_H
#define CARDS_H

#include <stdlib.h>
#include <time.h>
// Allocator of dynamic size cards array with
// autofree after going out of scope
#define CREATE_STACK(size) (card[(size)]){0}
// Converts an array of cards or a pointer to
// cards, if it decayed on to it from a function
// argument, into a general container with circular
// buffer
#define STACK_CARDS(cards, max_size)                                           \
  (card_stack){.cards = (cards), .capacity = (max_size), 0}
// This is equivalent to first allocating
// an autofree array and using it to get
// the general container with circular buffer
#define INIT_STACK(max_size)                                                   \
  (card_stack){.cards = CREATE_STACK(max_size), .capacity = max_size, 0}
#define INVALID_CARD                                                           \
  (card) { .s = UNSUITABLE, .r = UNRANCKED }
#define SAME_SUIT(a, b) ((a).s == (b).s)
#define SAME_RANK(a, b) ((a).r == (b).r)
#define COMPARE_EQ(a, b) (SAME_SUIT((a), (b)) * SAME_RANK((a), (b)))
// Compare Partially Equal cards
// 0 -> totally different
// 1 -> either the same suit, or the same rank
// 2 -> equal rank and suit
#define COMPARE_PEQ(a, b) (SAME_SUIT((a), (b)) + SAME_RANK((a), (b)))
// Checks for succeeding rank without to use
// as a component for various kinds of
// validation of legal moves over different games
#define NEXT_RANK(a, b) (((a).r - (b).r) == 1)
// Checks for preceding rank, as the above
// is intended for component of validation
// functions or macros
#define PREVIOUS_RANK(a, b) (((b).r - (a).r) == 1)
#define IS_OVER_WARP(a, b) (((a).r == K) * ((b).r == A))
#define IS_UNDER_WARP(a, b) (((a).r == A) * ((b).r == K))
#define IS_RED_SUIT(s) ((s == HEARTS) || (s == DIAMONDS))
#define IS_BLACK_SUIT(s) ((s == CLUBS) || (s == SPADES))
#define SAME_COLOR(a, b)                                                       \
  (IS_RED_SUIT((a).s) * IS_RED_SUIT((b).s) ||                                  \
   IS_BLACK_SUIT((a).s) * IS_BLACK_SUIT((b).s))
#define DIFFERENT_COLOR(a, b) !SAME_COLOR((a), (b))
#define STACK_IS_EMPTY(card_stack) ((card_stack)->number == 0)

typedef enum {
  UNSUITABLE = -1,
  HEARTS,   // ♥
  DIAMONDS, // ♦
  CLUBS,    // ♣
  SPADES,   // ♠
} suit;

typedef enum {
  UNRANCKED = -1,
  A,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  J,
  Q,
  K
} rank;

typedef struct {
  suit s;
  rank r;
} card;

// Generic circular array with
// buffer to represent a grouping
// of cards (stacked cards regardless
// of where you will draw from top
// or bottom), it is intended to be
// used as both stack and queue even
// at the same time
typedef struct {
  card *cards;
  size_t capacity;
  size_t number;
  size_t front;
  size_t rear;
} card_stack;

// Orders or initialize a deck
// Example Code 1:
//
//>card_stack deck = INIT_STACK(52);
//>new_deck(&deck);
//
//  Example Code 2:
//
//>shuffle(&deck);
//>new_deck(&deck); <- this will order
// the deck by suit and rank
void new_deck(card_stack *deck);
void swap_cards(card *a, card *b);
void shuffle(card_stack *stack);
// Pila pop (stack pop) returns
// INVALID_CARD if empty otherwise
// the last card contained in
// the stack of cards
card ppop(card_stack *stack);
// Queue popb (dequeue) returns
// INVALID_CARD if empty otherwise
// the oldest card contained in
// the stack of cards
card qpop(card_stack *queue);
// Same as above ppop but the stack
// of cards remains unchanged
card ppeek(card_stack *stack);
// Same as above qpop but the stack
// of cards remains unchanged
card qpeek(card_stack *stack);
// Pushes a card to the stack of
// cards it works the same as classic
// enqueue if using qpop.
int push(card a, card_stack *stack);
// Maybe you need to return a card to the
// stack of cards but without altering
// previous order and your last operation
// on the container was qpop, I got you!
int qunpop(card a, card_stack *stack);

#endif // !CARDS_H

#ifndef CARDS_H
#define CARDS_H

#include <stdlib.h>
#include <time.h>

#define CREATE_STACK(size) (card[(size)]){0}
#define STACK_CARDS(cards, max_size) (card_stack){.cards = (cards), .capacity = (max_size),0}
#define INIT_STACK(max_size) (card_stack){ .cards = CREATE_STACK(max_size), .capacity = max_size, 0}
#define INVALID_CARD (card){ .s = UNSUITABLE, .r = UNRANCKED}
#define COMPARE_EQ(a,b) (((a).s == (b).s) * ((a).r == (b).r))

typedef enum {
  UNSUITABLE = -1,
  HEARTS,   // ♥
  DIAMONDS, // ♦
  CLUBS,    // ♣
  SAPDES,   // ♠
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

typedef enum {
  NONE,
  EMPTY,
  HIDDEN,
  VISIBLE,
  SELECTED,
} card_state;

typedef struct {
  suit s;
  rank r;
} card;

typedef struct {
  card * cards;
  size_t capacity;
  size_t number;
  size_t front;
  size_t rear;
} card_stack;

void new_deck(card_stack *deck);
void swap_cards(card *a, card *b);
void shuffle(card_stack *stack);
card ppop(card_stack *stack);
card qpop(card_stack *queue);
card ppeek(card_stack *stack);
card qpeek(card_stack *stack);
card qpeek(card_stack *stack);
int push(card a, card_stack *stack);
int qunpop(card a, card_stack *stack);

#endif // !CARDS_H

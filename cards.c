#include "cards.h"

void new_deck(card_stack *deck){
  deck->number = 52;
  for(int s = 0; s < 4; s++){
    for (int r = 0; r< 13;r++) {
      deck->cards[ s*13 + r] = (card){ .s = s, .r = r };
    }
  }
}

void swap_cards(card *a, card *b){
  card t = *a;
  *a = *b;
  *b = t;
}

void shuffle(card_stack *stack){
  static int seeded = 0;
  if(!seeded){
    srand(time(NULL));
    seeded = 1;
  }
  for (size_t i = stack->number-1; i > 0; i--) {
    swap_cards(&stack->cards[i],
               &stack->cards[(rand()%(i + 1))]);
  }
}

card ppop(card_stack *stack){
  if(stack->number == 0){
    return INVALID_CARD;
  }
  stack->number--;
  if(stack->rear == 0){
    stack->rear = stack->capacity;
  }
  stack->rear--;
  return stack->cards[stack->rear];
}

card qpop(card_stack *queue){
  if(queue->number == 0){
    return INVALID_CARD;
  }
  queue->number--;
  card ret = queue->cards[queue->front++];
  if(queue->front == queue->capacity){
    queue->front = 0;
  }
  return ret;
}

card ppeek(card_stack *stack){
  if(stack->number == 0){
    return INVALID_CARD;
  }
  size_t index = (stack->rear == 0)? stack->capacity-1 : stack->rear-1;
  return stack->cards[index];
}

card qpeek(card_stack *stack){
  if(stack->number == 0){
    return INVALID_CARD;
  }
  return stack->cards[stack->front];
}

int push(card a, card_stack *stack){
  if(stack->number == stack->capacity) return 1;
  stack->cards[stack->rear++] = a;
  stack->number++;
  if(stack->rear == stack->capacity){
    stack->rear = 0;
  }
  return 0;
}

int qunpop(card a, card_stack *stack){
  if(stack->number == stack->capacity) return 1;
  stack->front = (stack->front == 0)? stack->capacity -1 : stack-> front -1;
  stack->number++;
  stack->cards[stack->front] = a;
  return 0;
}


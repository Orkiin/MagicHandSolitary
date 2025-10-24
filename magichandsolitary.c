#include "magichandsolitary.h"

int new_game(game_state_solitary *game){
    for (size_t i = 0; i < 4; i++) {
        game-> fundation[i] = (card_stack){ .cards = (game->_fundation_hand[i]), .capacity = 13, 0};
      }
    for (size_t i = 0; i < 7; i++) {
        game-> tableau[i] = (card_stack){ .cards = (game->_tableau[i]), .capacity = 19, 0};
    }
    game-> hand = (card_stack){ .cards = (game->_fundation_hand[4]), .capacity = 13, 0};
    game-> waste_stock = (card_stack){ .cards = (game->_waste_stock), .capacity = 24, 0};
    game-> window = (card_stack){ .cards = (game->_window), .capacity = 3, 0};

  printf("opening a new deck\r");
  card_stack deck = INIT_STACK(52);
  new_deck(&deck);
  printf("shuffling the new deck\r");
  shuffle(&deck);
  printf("dealing tableau\r");
  for (size_t r = 0; r < 7; r++) {
    for (size_t t = r; t < 7; t++) {
      card a = ppop(&deck);
      push(a,&(game->tableau[t]));
      game->tableau[t].front = t;
    }
  }
  printf("done tableau\r");
  printf("dealing stock\r");
  float percentage = 0.0;
  for (card a = ppop(&deck); !COMPARE_EQ(INVALID_CARD,a); a = ppop(&deck)) {
    printf("%f\r",100.0* percentage++/24.0);
    push(a,&(game->waste_stock));
  }
  printf("done stock\r");
  return 0;
}

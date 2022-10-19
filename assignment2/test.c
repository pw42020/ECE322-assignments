#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "card.h"
#include "player.h"
#include "deck.h"

/* function declaration */
void printBook( struct card *card );
int main( ) {
    unsigned char decklength = 52;

    shuffle();
    struct card deez;
    
    deal_player_cards( &user );

    struct hand* temp = user.card_list->next->next->next;

    printBook( temp );






   return 0;
}

void printBook( struct card *card ) {

    printf("Card suit: %c\n", card->suit);
    printf( "Card rank : %s\n", card->rank);
}

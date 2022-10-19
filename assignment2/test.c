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
    
    deal_player_cards( &user );

    struct hand* hand;
    hand = user.card_list;
    struct card top;
    struct card top2;

    unsigned char i;
    for(i = 0; i < 6; i++)
    {
        top = hand->top;

        printBook( &top );

        hand = hand->next;
    }

   return 0;
}
// testing method (ONLY USED FOR TESTING BECAUSE I KNOW IT WORKS LOL)
void printBook( struct card* card ) {

    printf("Card suit: %c\n", card->suit);
    printf( "Card rank : %s\n", card->rank);

    return;
}

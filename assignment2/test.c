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

    struct card card1 = {'H','J'};
    struct card card2 = {'D','J'};
    struct card card3 = {'C','J'};
    struct card card4 = {'S','J'};
    
    
    add_card( &user, &card1 );
    add_card( &user, &card2 );
    add_card( &user, &card3 );
    add_card( &user, &card4 );

    char booked = check_add_book( &user );

    printf("%c", booked);

   return 0;
}
// testing method (ONLY USED FOR TESTING BECAUSE I KNOW IT WORKS LOL)
void printBook( struct card* card ) {

    printf("Card suit: %c\n", card->suit);
    printf( "Card rank : %s\n", card->rank);

    return;
}

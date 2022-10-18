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
    
    unsigned char i;
    for (i = 0; i < 7; i++)
    {
        deez = deck_instance.list[i];
        add_card( &user, &deez );
    }

    deez = user.card_list->top;

    printBook( &deez );


    struct player* target;
    target = (struct player*)malloc(sizeof(struct player));

    char rank[2] = "10";

    struct card Card1 = {'H', rank};
    struct card* cptr = &Card1;

    //printf("Card suit: %c\n", cptr->suit);
    //printf( "Card rank : %s\n", cptr->rank);
 
    /* print Book1 info by passing address of Book1 */
    //add_card(target, &Card1);

    //printBook( &(target->card_list->top) );


   return 0;
}

void printBook( struct card *card ) {

    printf("Card suit: %c\n", card->suit);
    printf( "Card rank : %s\n", card->rank);
}

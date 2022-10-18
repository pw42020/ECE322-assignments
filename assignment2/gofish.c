#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gofish.h"
#include "player.h"
#include "card.h"
#include "deck.h"

int main(int args, char* argv[]) 
{
  unsigned char play = 1;
  unsigned char usergo = 1;

  while(play)
  {
    // initializing and shuffling deck
    //deck_instance = (struct deck*)malloc(sizeof(struct deck));
    shuffle();

    // adding user and computer to the stack
    //user = (struct player*)malloc(sizeof(struct player));
    //computer = (struct player*)malloc(sizeof(struct player));

    // dealing cards to the players
    deal_player_cards(&user);
    //deal_player_cards(&computer);

    // while there is still a card on the deck
    while(0) // deck_instance.top_card != 51
    {
      unsigned char yuh;
      unsigned char j;

      // printing out all beginning stuff before every move
      printf("Player 1's Hand - %s");

      // copying user over to temp variable to iterate through for for loop
      struct hand *temp = (struct hand*)malloc(sizeof(struct hand));
      temp = user.card_list;

      for(j=0; j < user.hand_size; j++)
      {
        printf("%s%s ", temp->top.rank,temp->top.suit);
    
        temp = temp->next; // iterating to next card in list
      }
      printf("\n");
      scanf("%d",yuh);

      printf("Player 1's Book - %s");
      for(j=0; j < (sizeof(user.book)/sizeof(char)); j++) { printf("%s ",user.book[j]); }
      printf("\n");

      printf("Player 2's Book - %s");
      for(j=0; j < (sizeof(computer.book)/sizeof(char)); j++) { printf("%s ",computer.book[j]); }
      printf("\n");

      if(usergo)
      {
        

        usergo = 0;
      }
      else
      {

        usergo = 1;
      }


    }// while(deck_instance->top_card != 51)

  }// while(play)

  

  return 0;
}

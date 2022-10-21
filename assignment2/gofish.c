#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gofish.h"
#include "player.h"
#include "card.h"
#include "deck.h"

void printStatement(int usergo, int cardreal, char chosen);
void printCardChosen( struct player* target, char player, char chosen );


int main(int args, char* argv[]) 
{
  unsigned char play = 1; // if the user wants to play again at the end of the game
  int usergo = 1; // 1 if user's turn, 0 if not
  int cardreal; // 1 if search() returns with a card, 0 if search() does not
  char chosen; // the chosen rank from the player
  int gameover = 0; // integer from player.gameover(), if 1, go through gameover sequence
  char playagain[2]; // scanf() variable that if Y, play = 1, if N, play = 0;
  char booked ='0'; // return of check_add_book()

  while(play)
  {
    // initializing and shuffling deck
    //deck_instance = (struct deck*)malloc(sizeof(struct deck));
    shuffle();

    // adding user and computer to the stack
    //user = (struct player*)malloc(sizeof(struct player));
    //computer = (struct player*)malloc(sizeof(struct player));


    user.book_total = 0;
    user.book_total = 0;
    

    // dealing cards to the players
    deal_player_cards( &user );
    deal_player_cards(&computer);

    // while there is still a card on the deck
    while( deck_instance.top_card != 51 && !gameover)
    {
      unsigned char j;

      // printing out all beginning stuff before every move
      //printing player 1's hand
      printf("Player 1's Hand - ");

      // copying user over to temp variable to iterate through for for loop
      struct hand* temp = user.card_list;

      for(j=0; j < user.hand_size; j++)
      {
        printf("%c%c ", temp->top.rank, temp->top.suit); // 
    
        temp = temp->next; // iterating to next card in list
      }
      printf("\n");


      // printing player 1's book
      printf("Player 1's Book - ");
      for(j=0; j < (sizeof(user.book)/sizeof(char)); j++)
      {
        if (user.book[j] != NULL) {printf("%c ",user.book[j]);}
      }
      printf("\n");


      // printing player 2's book
      printf("Player 2's Book - ");
      for(j=0; j < (sizeof(computer.book)/sizeof(char)); j++) 
      {
        if (computer.book[j] != NULL) {printf("%c ",computer.book[j]);}
      }
      printf("\n");

      /*
      // from here to line 81: printing player 2's hand for debug
      printf("---------------------------------------------------------\n");

      printf("Player 2's Hand - ");

      temp = computer.card_list;

      for(j=0; j < computer.hand_size; j++)
      {
        printf("%s%c ", temp->top.rank,temp->top.suit);
    
        temp = temp->next; // iterating to next card in list
      }
      printf("\n");*/

      if(usergo)
      {
        chosen = user_play( &user ); // returns rank user wants to search computer for

        cardreal = search(&computer, chosen);

        // if computer has chosen rank
        if(cardreal) 
        { 
          printStatement( usergo, cardreal, chosen );

          transfer_cards( &computer, &user, chosen );

          booked = check_add_book( &user ); // check if user has 4 of any rank
          if (booked != 0) { printf("Player 1 books %c\n",chosen); };

          usergo = 1; // user goes again

        } else {
          
          printStatement( usergo, cardreal, chosen);

          add_card( &user, next_card());

          booked = check_add_book( &user ); // check if user has 4 of any rank
          if (booked != 0) { printf("Player 1 books %c\n",booked); };

          usergo = 0; // computer now goes
        }
      }
      else // computer's turn
      {
        chosen = computer_play(&computer);

        cardreal = search(&user, chosen);

        if (cardreal) // if user has a card of rank chosen
        {
          printStatement( usergo, cardreal, chosen);
          transfer_cards( &user, &computer, chosen );

          booked = check_add_book( &computer ); // check if computer has 4 of any rank
          if (booked != 0) { printf("Player 2 books %c\n",booked); };

          usergo = 0;
        } else { // if user does not have a card of rank chosen, computer goes fish

          printStatement( usergo, cardreal, chosen );

          add_card( &computer, next_card());

          booked = check_add_book( &computer ); // check if computer has 4 of any rank
          if (booked != 0) { printf("Player 2 books %c\n",booked); };

          usergo = 1;
        }
      }

      booked = 0; // IMPORTANT: MAKES SURE BOOKED REMAINS NOT INITIALIZED

      // if either player runs out of cards, redeal them seven cards
      if(user.hand_size == 0 && !gameover)
      {
        deal_player_cards( &user );
      }
      if(computer.hand_size == 0 && !gameover)
      {
        deal_player_cards( &computer );
      }
      
      // check if either player has 7 points so the game is won
      if(game_over( &user ))
      {
        printf("Player 1 Wins! 7-%d\n", computer.book_total);
        while(playagain[0] != 'Y' && playagain[0] != 'N')
        {
          printf("Would you like to play again? [Y/N] ");
          scanf("%s", playagain);

          if(playagain[0] != 'Y' && playagain[0] != 'N')
          {
            printf("Please enter something valid");
          }
        } // while playagain not Y or N
      } // if gameover user
      if(game_over( &computer ))
      {
        printf("Player 2 Wins! 7-%d\n", user.book_total);

        // while user does not provide sufficient input
        while(playagain[0] != 'Y' && playagain[0] != 'N')
        {
          printf("Would you like to play again? [Y/N] ");
          scanf("%s", playagain);

          if(playagain[0] != 'Y' && playagain[0] != 'N')
          {
            printf("Please enter something valid");
          }
        }// while playagain not Y or N
      }// if gameover computer

      if(playagain[0]=='Y')
      {
        printf("Shuffling deck...\n\n");
        reset_player( &computer );
        reset_player( &user );

      }
    }// while(deck_instance->top_card != 51)

    printf("Exiting.\n");

  }// while(play)

  

  return 0;
}

void printBook( struct card *card ) {

    printf("Card suit: %s\n", card->suit);
    printf( "Card rank : %c\n", card->rank);
}// void printBook()

void printStatement(int usergo, int cardreal, char chosen)
{
  char array[2] = {'2','1'}; // made so if usergo = 0 (computer play) then array[0] == player 2 prints first

  if (cardreal)
  {
    if(usergo){
      printCardChosen( &user, array[usergo], chosen );
      printCardChosen( &computer, array[usergo - 1], chosen);
    } else {
      printCardChosen( &computer, array[usergo], chosen);
      printCardChosen( &user, array[usergo + 1], chosen );
    } // if usergo



  } else {
    int user2;
    if (usergo) {user2 = usergo - 1;} else {user2 = usergo + 1;}

    printf("   -Player %c has no %c's\n", array[user2], chosen);
    printf("   -GoFish, Player %c draws a card\n", array[usergo]);
    printf("   -Player %c's turn\n", array[user2]);

  } // else
} // void printStatement()

void printCardChosen( struct player* target, char player, char chosen )
{
  printf("   -Player %c's Hand - ", player);

  // copying user over to temp variable to iterate through for for loop
  struct hand* temp = target->card_list;

  unsigned char j;
  for(j=0; j < target->hand_size; j++)
  {
    // if card from hand has same rank as chosen, print it
    if (temp->top.rank == chosen) { printf("%c%c ", temp->top.rank,temp->top.suit); }

    temp = temp->next; // iterating to next card in list
  }
  printf("\n");
} // void printCardChosen()
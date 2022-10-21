#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gofish.h"
#include "player.h"
#include "card.h"
#include "deck.h"

// Patrick Walsh & Evan Raftery, ECE 322, Fall 2022

void printBooks();
char endGame();
void printStatement(int usergo, int cardreal, char chosen);
void printCardChosen( struct player* target, char player, char chosen );

int main(int args, char* argv[])		// Patrick Walsh
{
	unsigned char play = 1; 	// If the user wants to play again at the end of the game
  	int usergo = 1; 		// 1 if user's turn, 0 if not
  	int cardreal; 			// 1 if search() returns with a card, 0 if search() does not
  	char chosen; 			// The chosen rank from the player
  	int gameover = 0; 		// Integer from player.gameover(), if 1, go through gameover sequence
  	char playagain; 		// Scanf() variable that if Y, play = 1, if N, play = 0;
  	char booked ='0'; 		// Return of check_add_book()

  	while(play)
  	{
    		usergo = 1;
    		// Initializing and shuffling deck
    		// Deck_instance = (struct deck*)malloc(sizeof(struct deck));
    		shuffle();

    		// adding user and computer to the stack
    		// user = (struct player*)malloc(sizeof(struct player));
    		// computer = (struct player*)malloc(sizeof(struct player));

    		user.book_total = 0;
    		computer.book_total = 0;

    		// Dealing cards to the players
    		deal_player_cards( &user );
    		deal_player_cards(&computer);

    		// While there is still a card on the deck
    		while( deck_instance.top_card != 52 && !gameover)
    		{
      			unsigned char j;

      			// Printing out all beginning stuff before every move
      			// Printing player 1's hand
      			printf("Player 1's Hand - ");

      			// Copying user over to temp variable to iterate through for for loop
      			struct hand* temp = user.card_list;

      			for(j=0; j < user.hand_size; j++)
      			{
        			printf("%c%c ", temp->top.rank, temp->top.suit);
        			temp = temp->next; // Iterating to next card in list
      			}
      			printf("\n");
      			printBooks();

      			printf("---------------------------------------------------------\n");

      			if(usergo)
      			{
        			chosen = user_play( &user ); // Returns rank user wants to search computer for

        			cardreal = search(&computer, chosen);

        			// If computer has chosen rank
        			if(cardreal)
        			{
          				printStatement( usergo, cardreal, chosen );

          				transfer_cards( &computer, &user, chosen );

          				booked = check_add_book( &user ); // Check if user has 4 of any rank
          				if (booked != 0) { printf("Player 1 books %c\n",chosen); };

          				usergo = 1; // User goes again
          				printf("   -Player 1 gets another turn\n");

        			} else {

          				printStatement( usergo, cardreal, chosen);

          				add_card( &user, next_card());

          				if(user.card_list->top.rank == chosen)
          				{
            					printf("   -Player 1 gets another turn\n");

            					usergo = 1; // Computer now goes
          				} else {
            					usergo = 0;
            					printf("   -Player 2's turn\n");
          				}

          				booked = check_add_book( &user ); // Check if user has 4 of any rank
          				if (booked != 0) { printf("Player 1 books %c\n",booked); };
        			}
      			}
      			else // Computer's turn
      			{
        			chosen = computer_play(&computer);

        			printf("Player 2, enter a rank: %c\n", chosen);

        			cardreal = search(&user, chosen);

        			if (cardreal) // If user has a card of rank chosen
        			{
          				printStatement( usergo, cardreal, chosen);
          				transfer_cards( &user, &computer, chosen );

          				booked = check_add_book( &computer ); // Check if computer has 4 of any rank
          				if (booked != 0) { printf("Player 2 books %c\n",booked); };

          				usergo = 0;
          				printf("   -Player 2 gets another turn\n");
        			} else { // If user does not have a card of rank chosen, computer goes fish

          				printStatement( usergo, cardreal, chosen );

          				add_card( &computer, next_card());

          				if(computer.card_list->top.rank == chosen)
          				{
            					usergo = 0; // Computer now goes
            					printf("   -Player 2 gets another turn\n");
          				} else {
            					usergo = 1;
            					printf("   -Player 1's turn\n");
          				}

          				booked = check_add_book( &computer ); // Check if computer has 4 of any rank
          				if (booked != 0) {
            					printf("Player 2 books %c\n",booked);
          				}
        			}// Else inside else
      			}// Else

      			booked = 0; // IMPORTANT: MAKES SURE BOOKED REMAINS NOT INITIALIZED

      			// If either player runs out of cards, redeal them seven cards
      			if(user.hand_size == 0 && !gameover)
      			{
        			add_card( &user, next_card() );
      			}
      			if(computer.hand_size == 0 && !gameover)
      			{
        			add_card( &computer, next_card() );
      			}

      			// Breaking the game if someone got 7 cards
      			if(game_over( &user ) || game_over( &computer )) { break; }

      			printf("\n");

    		}// While(deck_instance->top_card != 51)

    		// If end game, print who won or if there was a tie
    		if(computer.book_total > user.book_total){ printf("Player 2 Wins! %d-%d\n", computer.book_total, user.book_total); }
    		else if(computer.book_total < user.book_total){ printf("Player 1 Wins! %d-%d\n",user.book_total, computer.book_total); }
    		else { printf("Tie!\n"); }
    		printBooks();

    		playagain = endGame();
    		if(playagain == 'Y')
    		{
      			printf("Shuffling deck...\n\n");
      			reset_player( &computer );
      			reset_player( &user );
    		} else {
      			printf("Exiting.\n");
      			break;
    		}
  	}// While(play)
  return 0;
}

void printBooks()	// Patrick Walsh
{
  	unsigned char j;
  	// Printing player 1's book
  	printf("Player 1's Book - ");
  	for(j=0; j < (sizeof(user.book)/sizeof(char)); j++)
  	{
    		if (user.book[j] != NULL) {printf("%c ",user.book[j]);}
  	}
  	printf("\n");

  	// Printing player 2's book
  	printf("Player 2's Book - ");
  	for(j=0; j < (sizeof(computer.book)/sizeof(char)); j++) 
  	{
    		if (computer.book[j] != NULL) {printf("%c ",computer.book[j]);}
  	}
  	printf("\n");
}

void printStatement(int usergo, int cardreal, char chosen)	// Patrick Walsh
{
  	char array[2] = {'2','1'}; // Made so if usergo = 0 (computer play) then array[0] == player 2 prints first

  	if (cardreal)
  	{
    		if(usergo){
      			printCardChosen( &user, array[usergo], chosen );
      			printCardChosen( &computer, array[usergo - 1], chosen);
    		} else {
      			printCardChosen( &computer, array[usergo], chosen);
      			printCardChosen( &user, array[usergo + 1], chosen );
    		} // If usergo
  	} else {
    		int user2;
    		if (usergo) {user2 = usergo - 1;} else {user2 = usergo + 1;}

    		printf("   -Player %c has no %c's\n", array[user2], chosen);
    		printf("   -GoFish, Player %c draws a card\n", array[usergo]);

  	} // Else
} // VOid printStatement()

void printCardChosen( struct player* target, char player, char chosen )		// Patrick Walsh
{
  	printf("   -Player %c's Hand - ", player);

  	// Copying user over to temp variable to iterate through for for loop
  	struct hand* temp = target->card_list;

  	unsigned char j;
  	for(j=0; j < target->hand_size; j++)
  	{
    		// If card from hand has same rank as chosen, print it
    		if (temp->top.rank == chosen) { printf("%c%c ", temp->top.rank,temp->top.suit); }

    		temp = temp->next; // Iterating to next card in list
  	}
  	printf("\n");
} // Void printCardChosen()

char endGame()		// Patrick Walsh
{
  	char playagain[2];

  	while(playagain[0] != 'Y' && playagain[0] != 'N')
  	{
  		printf("Would you like to play again? [Y/N] ");
    		scanf("%s", playagain);

    		if(playagain[0] != 'Y' && playagain[0] != 'N')
    		{
      			printf("Please enter something valid\n");
    		}
  	}
	return playagain[0];

  	printf("\n"); // Adding a little extra space to tell where the program is better
}

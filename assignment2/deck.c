#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int shuffle();
int deal_player_cards(struct player* target);
struct card* next_card( );
size_t deck_size( );


// Function to intialize deck, shuffle cards O(n^2) time
int shuffle()	// Patrick Walsh
{
	deck_instance.top_card = 0;
  	unsigned char decklength = 52;
  	// Initializing arrays suits and ranks to make easy initialization for deck
  	char suits[4] = {'H','S','D','C'};
  	char ranks[13] = {'A','2','3','4','5','6','7','8','9','X','J','Q','K'};

  	// Initializing first array
  	struct card temparray[decklength];

  	// Array to keep track of random numbers given by C
  	int array[52] = {0};


  	unsigned char i;
  	char suit = -1; // Rank count
  	for(i = 0; i < decklength; i++)
  	{
    		if(i % 13 == 0)
    		{
      			suit += 1;
    		} // If statement
    		struct card temp = {suits[suit], ranks[i % 13]};

    		temparray[i] = temp;

  	} // For loop

  	// While the entirety of temparray hasn't been assigned to lis, keep getting random numbers
  	int num;
  	unsigned char inArr; // Boolean inArray
  	i = 0;
  	unsigned char j = 0;
  	while(j != decklength)
  	{
    		inArr = 0;
    		num = (rand() % (decklength));

    		// Checks if num is already in array

    		for(i = 0; i < 52; i++)
    		{
      			if(array[i] != 0)
      			{
        			if(num == array[i])
        			{
          				inArr = 1;
        			}
      			}
    		}// For loop

    		// If random number has not already been chosen
    		if(!inArr)
    		{
      			deck_instance.list[j] = temparray[num];

      			// Putting number into chosen number array
      			array[j] = num;
      			j += 1;
    		} // If (!inArr)

  	} // While loops
  	return 0;
} // Int shuffle()

int deal_player_cards(struct player* target)	// Patrick Walsh
{
    	// For loop to instantiate player's and pc's hands
    	unsigned char i;
    	int inittopcard = deck_instance.top_card;

    	for(i = 0; i < 7; i++)
    	{
        	add_card(target, next_card());
    	} // For loop instantiating player hands

    	return 0;
}

struct card* next_card()	// Patrick Walsh
{
    	struct card* next_card;

    	next_card = &deck_instance.list[deck_instance.top_card];

    	deck_instance.top_card += 1;

    	return next_card;
}

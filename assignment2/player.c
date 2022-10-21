#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"


int add_card(struct player* target, struct card* new_card)	// Evan Raftery & Patrick Walsh
{
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));	// Temp pointer for adding the new card

	temp->top = *new_card;
	temp->next = target->card_list;		// New_card is now at the top of our hand

	target->card_list = temp;
	target->hand_size += 1; 		// Increment hand_size

	return 0;
}

int remove_card(struct player* target, struct card* old_card)	// Evan Raftery
{
	struct hand* iterator = target->card_list;	// Temp pointers for iterating through the hand
	struct hand* previous = NULL;
	if (iterator == NULL)	// Check for empty hand
	{
		return -1;
	}
	while (1)	// While the card is not found...
	{
		if(target->hand_size == 1) { break; }
		if (iterator == NULL)		// If at end of hand (If card not found)
		{
			return -1;
		}
		if (iterator->top.rank == old_card->rank && iterator->top.suit == old_card->suit)	// Found
		{
			break;
		}
		previous = iterator;		// Iterate
		iterator = iterator->next;
	}
	if (previous != NULL)	// Fill the gap made by the removed card in the linked list
	{
		previous->next = iterator->next;
	}
	else
	{
		target->card_list = iterator->next;
	}
	target->hand_size--;	// Decrement hand size
	free(iterator);		// Free the memory of the removed card
	return 0;
}

char check_add_book(struct player* target)	// Evan Raftery
{
	char ranks[13] = {'A','2','3','4','5','6','7','8','9','X','J','Q','K'};
	unsigned char index;
	char rank;
	for(index = 0; index < 13; index++)	// Check every possible card, remove first book found
	{
		rank = ranks[index];
		struct hand* iterator = target->card_list;	// Temp pointer for iterating through the hand
		int count = 0;					// Running count of how many matches we've found for a certain rank
		if (iterator == NULL)		// Return 0 if empty hand
		{
				return 0;
		}
		while (iterator != NULL)	// Iterate through entire hand
		{
		if (iterator->top.rank == rank)	// Match found
		{
			count++;
		}
				iterator = iterator->next;	// Iterate
		}
		if (count != 4)		// If we find a book, stop checking and add it
		{
			continue;
		}
		iterator = target->card_list;	// Reset our temp pointer
		while (iterator != NULL)	// Now let's remove the cards and add them to the book
		{
			if (iterator->top.rank == rank)	// Found - remove card (we free the memory in remove_card)
			{
				remove_card(target, &(iterator->top));
			}
			iterator = iterator->next;	// Iterator
		}
		for (int i = 0; i < 7; i++)	// Find an empty slot in the player's book and add the rank to the book
		{
			if (target->book[i] == 0)
			{
				target->book[i] = rank;
				target->book_total ++; // Increment book_total (number of books a player has made)
				return rank;
			}
		}
	}
        return 0;
}


int search(struct player* target, char rank)	// Evan Raftery
{
	struct hand* iterator = target->card_list;	// Temp pointer for iterating through the hand
	if (iterator == NULL)		// Check for empty hand
	{
			return 0;
	}
	unsigned char i;
	for(i = 0; i < target->hand_size; i++)
	{
		if (iterator->top.rank == rank)		// If match found
		{
			return 1;
		}
		iterator = iterator->next;
	}
	return 0;
}

int transfer_cards(struct player* src, struct player* dest, char rank)		// Evan Raftery
{
	struct hand* iterator = src->card_list;		// Temp pointers to iterate through the hand
	unsigned char found = 0;
	unsigned char count = 0;
	if (iterator == NULL)		// No cards in hand
	{
			return 0;
	}
	while (iterator != NULL)	// Check the hand for the requested rank
	{
	if (iterator->top.rank == rank)	// If match found
	{
		add_card(dest, &(iterator->top));
		remove_card(src, &(iterator->top));
		count++;		// Keep track of number found
		found = 1;		// Set Boolean for "Have we found a card?" to True
	}
		iterator = iterator->next;	// Iterate
	}
	if (found)	// Cards transferred - return number moved
	{
		return count;
	}
        if (!found)	// No cards transferred - return 0
	{
		return 0;
	}
	return 0;	// Program will not reach here, but we assume none transferred if it does - also clears up a warning
}

int game_over(struct player* target)	// Evan Raftery
{
	if(target->book[6] != 0)
	{
		return 1;
	}
	return 0;
}

int reset_player(struct player* target)		// Evan Raftery
{
	target->book_total = 0;		// Reset book total

	for (unsigned char i = 0; i < 7; i++)	// Reset book values to 0
	{
		target->book[i] = 0;
	}
    	struct hand* newtemp = target->card_list;	// Iterator
	struct hand* oldtemp;
    	if (newtemp == NULL)		// If hand is already empty
    	{
         	return 0;
    	}
    	while (target->hand_size > 0)		// While hand is not empty, remove the top card
    	{
		oldtemp = newtemp->next;
		remove_card(target, &(newtemp->top));

		newtemp = oldtemp;
    	}
	return 0;
}

char computer_play(struct player* target)	// Evan Raftery
{
	struct hand* iterator = target->card_list;	// Temp pointer to iterate through hand
	unsigned char index = rand() % target->hand_size;	// Pick a random index to get the computer's choice
	unsigned char i = 0;
	while(i != index)
	{
		iterator = iterator->next;	// Find the card corresponding to the choice
		i++;
	}

	return iterator->top.rank;	// Return the rank of the choice made
}

char user_play(struct player* target)		// Patrick Walsh
{
	unsigned char error = 0;
    	while(error == 0)
    	{
		// Entering rank, set in val (10 is X)
        	char val[2];
        	printf("Player 1's turn, enter a Rank: ");
        	scanf("%s", &val);

		// Error checking to ensure player has at least one card of requested rank

        	struct hand *temp = target->card_list;

		// Checking if user has a card with the same rank as requested
        	unsigned char i;
        	for(i = 0; i < target->hand_size; i++)
        	{
            		if(temp->top.rank == val[0])
			{
				error = 1;
				return temp->top.rank;
			}
            		temp = temp->next;
        	}
        	printf("Error - must have at least one card from rank to play\n");
    	}
	return -1;	// Program will never reach here, but we throw an error if it does - also clears up a warning
}

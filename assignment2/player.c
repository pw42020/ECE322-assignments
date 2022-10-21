#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include <string.h>




int add_card(struct player* target, struct card* new_card)
{
	// getting temp ready
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));
	
	temp->top = *new_card;
	temp->next = target->card_list;


	// new_card is now the top of the linked list card_list stack
	target->card_list = temp;

	target->hand_size += 1; // adding 1 to hand_size

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
		if (iterator == NULL)		// If at end of hand (If card not found)
		{
			return -1;
		}
		if (iterator->top.rank == old_card->rank && iterator->top.suit == old_card->suit)		// Found
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
				target->book_total ++; // adding to target's book table 1
				return rank;
				//break;
			}
		}
	}
        return 0; // return rank;	//NOTE TO SELF: THIS FUNCTION CHECKS FOR ALL BOOKS AT ONCE! IF YOU NEED TO CHANGE IT TO DO ONLY 1, PUT THIS RETURN STATEMENT AFTER YOU ASSIGN THE CHAR IN THE BOOK!
}


int search(struct player* target, char rank)
{
	struct hand* iterator = target->card_list;
	struct hand* previous = NULL;
	if (iterator == NULL)
	{
			return 0;
	}
	unsigned char i;
	for(i = 0; i < target->hand_size; i++)
	{

			if (iterator->top.rank == rank) // NEED THE INDEX!!!
			{
				return 1;
			}
			previous = iterator;
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
}

int game_over(struct player* target)
{
	if(target->book_total == 7)
	{
		return 1;
	}
	return 0;
}

int reset_player(struct player* target)
{
	for (unsigned char i = 0; i < 7; i++)
	{
		target->book[i] = 0;
	}
	struct hand* iterator = target->card_list;
	struct hand* previous = NULL;
	if (iterator == NULL)
	{
			return 0;
	}
	while (iterator != NULL)
	{
			previous = iterator;
			iterator = iterator->next;
	remove_card(target, &(iterator->top));
	free(iterator);
	}

	return 0;

}

char computer_play(struct player* target)
{
	struct hand* iterator = target->card_list;
	struct hand* previous = NULL;
	unsigned char index = rand() % target->hand_size;
	unsigned char i = 0;
	while(i != index)
	{
		previous = iterator;
		iterator = iterator->next;
		i++;
	}

	return iterator->top.rank;
}

char user_play(struct player* target)
{
    unsigned char error = 0;
    while(error == 0)
    {	
		// entering rank, set in val (10 is X)
        char val[2];
        printf("Player 1's turn, enter a Rank: ");
        scanf("%s", &val);
        
        // error checking to ensure player has at least one card of requested rank

        struct hand *temp = target->card_list;

		// checking if user has a card with the same rank as requested
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
}

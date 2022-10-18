#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include <string.h>




int add_card(struct player* target, struct card* new_card)
{

	// getting temp ready
	struct hand temp;

	// new_card is now the top of the linked list card_list stack
	temp.top = *new_card;
	temp.next = target->card_list;
	target->card_list = &temp;

	return 0;
}

int remove_card(struct player* target, struct card* old_card)
{
	struct hand* iterator = target->card_list;
	struct hand* previous = NULL;
	if (iterator == NULL)
	{
		return -1;
	}
	while (&(iterator->top) != old_card)
	{
		previous = iterator;
		iterator = iterator->next;
		if (iterator == NULL)
		{
			return -1;
		}
	}
	if (previous != NULL)
	{
		previous->next = iterator->next;
	}
	else
	{
		target->card_list = iterator->next;
	}
	free(iterator);
	return 0;
}

char check_add_book(struct player* target)
{
	struct hand* iterator = target->card_list;
        struct hand* previous = NULL;
	unsigned char rank = iterator->top.rank;
	unsigned char count = 0;
        if (iterator == NULL)
        {
                return 0;
        }
        while (iterator != NULL)
        {
		if (iterator->top.rank == rank)
		{
			count++;
		}
                previous = iterator;
                iterator = iterator->next;
        }
	if (count != 4)
	{
		return 0;
	}
	iterator = target->card_list;
	previous = NULL;
	while (iterator != NULL)
	{
                if (iterator->top.rank == rank)
                {
                        remove_card(target, &(iterator->top));
			free(iterator);
                }
                previous = iterator;
                iterator = iterator->next;
	}
	for (int i = 0; i < 7; i++)
	{
		if (target->book[i] == 0)
		{
			target->book[i] = rank;
			break;
		}
	}
        return rank;
}

int search(struct player* target, char rank)
{
	struct hand* iterator = target->card_list;
        struct hand* previous = NULL;
        if (iterator == NULL)
        {
                return 0;
        }
        while (iterator->top.rank != rank)
        {
                previous = iterator;
                iterator = iterator->next;
                if (iterator == NULL)
                {
                        return 0;
                }
        }
        return 1;
}

int transfer_cards(struct player* src, struct player* dest, char rank)
{
	struct hand* iterator = src->card_list;
    struct hand* previous = NULL;
	unsigned char found = 0;
	unsigned char count = 0;
        if (iterator == NULL)
        {
                return 0;
        }
        while (iterator != NULL)
        {
		if (iterator->top.rank == rank)
		{
			add_card(dest, &(iterator->top));
			remove_card(src, &(iterator->top));
			count++;
		}
                previous = iterator;
                iterator = iterator->next;
        }
	if (found)
	{
		return count;
	}
        if (!found)
	{
		return 0;
	}
}

int game_over(struct player* target)
{
	if (target->book[6] != 0)
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
	int chosen = iterator->top.rank;
	return chosen;
}

char user_play(struct player* target)
{
    unsigned char error = 0;
    while(error == 0)
    {
        char* val = (char*)malloc(sizeof(char)*3);
        printf("Player 1's turn, enter a Rank: ");
        scanf("%s\n",&val);
        
        // error checking to ensure player has at least one card of requested rank

        struct hand *temp = (struct hand*)malloc(sizeof(target->card_list));
        memcpy(temp, target->card_list,sizeof(target->card_list));

        unsigned char i;
        for(i = 0; i < target->hand_size; i++)
        {
            if(val==temp->top.rank){ error = 1; free(val); return val; }

            temp = temp->next;
        }

        printf("Error - must have at least one card from rank to play");
    }
}


#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int shuffle();
int deal_player_cards(struct player* target);
struct card* next_card( );
size_t deck_size( );



//function to intialize deck, shuffle cards O(n^2) time
int shuffle()
{
  
  deck_instance.top_card = 0;
  unsigned char decklength = 52;
  // initializing arrays suits and ranks to make easy initialization for deck
  char suits[4] = {'H','S','D','C'};
  char ranks[13] = {'A','2','3','4','5','6','7','8','9','10','J','Q','K'};

  // initializing first array
  struct card temparray[decklength];
  
  // array to keep track of random numbers given by C
  int array[52] = {0};


  unsigned char i;
  char suit = -1; // rank count 
  for(i = 0; i < decklength; i++)
  {
    if(i % 14 == 0)
    {
      suit += 1;
    }// if statement
    struct card temp = {suits[suit], ranks[i % 14]};

    temparray[i] = temp;

  }// for loop

  // while the entirety of temparray hasn't been assigned to lis, keep getting random numbers
  int num;
  unsigned char inArr; // boolean inArray
  i = 0;
  unsigned char j = 0;
  while(j != decklength)
  {
    inArr = 0;
    num = (rand() % (decklength));

    // CHECKS IF NUM IS ALREADY IN ARRAY
    
    for(i = 0; i < 52; i++)
    {
      //printf("Deez\n");
      //printf("%d\n",array[i]);
      if(array[i] != 0)
      {
        if(num == array[i])
        {
          inArr = 1;
        }
      }
    }// for loop

    // if random number has not already been chosen
    if(!inArr)
    {
      printf("%d\n",j);
      deck_instance.list[j] = temparray[num];
      //printf("%d\n",num);

      // putting number into chosen number array
      array[j] = num;
      j += 1;
    } // if (!inArr)

  }// while loops

  return 0;
}// int shuffle()

int deal_player_cards(struct player* target)
{
    // for loop to instantiate player's and pc's hands
    unsigned char i;
    int inittopcard = deck_instance.top_card = malloc(sizeof(int));

    for(i = inittopcard; i < inittopcard + 7; i++)
    {
        if(i > 52) return 1; // if error occurs

        add_card(target, next_card());

    }// for loop instantiating player hands

    return 0;
}

struct card* next_card()
{
    deck_instance.top_card += 1;
    return &deck_instance.list[deck_instance.top_card - 1];
}
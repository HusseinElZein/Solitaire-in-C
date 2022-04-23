#include <stdio.h>

typedef struct CardNode Card;
int addCard(Card *newCard, Card **list);
Card *C1 = NULL;

struct CardNode{
    Card *next;
    Card *prev;
    char number;
    char suit;
};

int main(){

    Card card = {NULL,NULL,'2','H'};
    Card card1 = {NULL,NULL,'3','K'};
    Card card2 = {NULL, NULL, '4', 'P'};


    addCard(&card, &C1);
    addCard(&card1, &C1);
    addCard(&card2, &C1);


    //This should say H
    printf("%c", C1->suit);

    //This should say K
    printf("\n" "%c", C1->next->suit);

    //This should say P
    printf("\n" "%c", C1->next->next->suit);
}



int addCard(Card *newCard, Card **list){

    Card *current = list;

    if(*list == NULL) {
        *list = newCard;
    }

    while(current->next != NULL) {
        current = current->next;

        if(current->next == NULL){
            current->next = newCard;
            newCard->prev = current;
            newCard->next = NULL;
            break;
        }
    }
    return 0;
}




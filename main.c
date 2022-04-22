#include <stdio.h>


typedef struct CardType Card;

struct CardType{
    Card *next;
    Card *prev;
    char number;
    char suit;
};

Card *c1 = NULL;
Card *c2 = NULL;
Card *c3 = NULL;
Card *c4 = NULL;
Card *c5 = NULL;
Card *c6 = NULL;
Card *c7 = NULL;

Card *f1 = NULL;
Card *f2 = NULL;
Card *f3 = NULL;
Card *f4 = NULL;



int addCard(Card *newCard, Card **list){

    Card *current = list;

    if(*list == NULL){
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

int main() {
    Card card = {NULL,NULL,'2','H'};

    Card card1 = {NULL,NULL,'3','K'};


    addCard(&card, &c1);
    addCard(&card1, c1);

    printf("%c", c1->suit);
    printf("\n" "%c", c1->next->suit);

    return 0;
}







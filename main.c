#include <stdio.h>

typedef struct cardType Card;

struct cardType {
    Card *next;
    Card *prev;
    char number;
    char suit;
};

Card *C1 = NULL;
Card *C2 = NULL;
Card *C3 = NULL;
Card *C4 = NULL;
Card *C5 = NULL;
Card *C6 = NULL;
Card *C7 = NULL;

Card *F1 = NULL;
Card *F2 = NULL;
Card *F3 = NULL;
Card *F4 = NULL;

int addCard(Card *newCard, Card **list){
    Card *current = (Card *) list;

    if (*list == NULL) {
        *list = newCard;
    }

    while (current->next != NULL) {
        current = current->next;

        if (current->next == NULL){
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


    addCard(&card, &C1);
    addCard(&card1, &C1);

    printf("%c", C1->suit);
    printf("\n" "%c", C1->next->suit);

    return 0;
}







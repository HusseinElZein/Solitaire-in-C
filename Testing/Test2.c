#include <stdio.h>
#include <stdlib.h>

typedef struct CardNode Card;
typedef struct PileNode Pile;

struct CardNode{
    Card *next;
    Card *prev;
    char number;
    char suit;
    char isHidden;
};

struct PileNode {
    Card *head;
    Card *tail;
    int sizeOfPile;
};

//This returns the tail of a given pile
Card* chooseTailCardFromPile(Pile pile) {
    return pile.tail;
}

int main() {
    /**Inserting into a pile one time**/
    Pile *C1 = malloc(sizeof(Pile));
    C1->tail = NULL;
    Card card = {NULL,NULL,'2','H','0'};

    C1->tail = &card;

    printf("%c",chooseTailCardFromPile(*C1)->suit);

    return 0;
}
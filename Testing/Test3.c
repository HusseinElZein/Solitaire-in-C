#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char message[256] = "HELLO";
char lastCommand[64] = "NONE";

//This returns the next card number in the hierachy
char canBeMoved(char numberOfCardMoved) {

    switch (numberOfCardMoved) {
        case 'A': return '2';
        case '2': return '3';
        case '3': return '4';
        case '4': return '5';
        case '5': return '6';
        case '6': return '7';
        case '7': return '8';
        case '8': return '9';
        case '9': return 'T';
        case 'T': return 'J';
        case 'J': return 'Q';
        case 'Q': return 'K';
        default: return '0';
    }
}

//This moves one card to the bottom of a pile
void moveCardToPile(Card *cardMoved, Pile *pile) {

    if (pile->sizeOfPile == 0) {
        pile->head = cardMoved;
        pile->tail = cardMoved;
        pile->sizeOfPile++;
        strcpy(message, "OK");
        return;
    }

    if (pile->tail != NULL && cardMoved->suit != pile->tail->suit
        && canBeMoved(cardMoved->number) == pile->tail->number) {
        cardMoved->prev = pile->tail;
        cardMoved->next = NULL;
        pile->tail->next = cardMoved;
        pile->tail = cardMoved;
        pile->sizeOfPile++;
        strcpy(message, "OK, card moved");
    } else {
        strcpy(message, "error, card cannot be moved");
    }
}

//This returns the tail of a given pile
Card* chooseTailCardFromPile(Pile pile) {
    return pile.tail;
}

//This removes the tail from a given pile
void removeCardFromPile(Pile *pile) {

    if (pile->sizeOfPile != 0) {

        if (pile->sizeOfPile > 1) {
            pile->tail = pile->tail->prev;
            pile->tail->isHidden = 0;
            pile->tail->next = NULL;
        } else if (pile->sizeOfPile == 1) {
            pile->tail = NULL;
            pile->head = NULL;
        }
        strcpy(message, "OK");
    } else {
        strcpy(message, "error, empty pile");
    }
    pile->sizeOfPile--;
}

int main() {

    /**Inserting two cards with moveCardToPile method, then removing them**/
    Card card = {NULL, NULL, '2', 'H', '0'};

    Card card1 = {NULL, NULL, 'A', 'S', '0'};

    Pile *C1 = malloc(sizeof(Pile));
    C1->sizeOfPile = 0;
    C1->tail = NULL;
    C1->head = NULL;

    moveCardToPile(&card, C1);
    printf("%s \n", message); //message after first card insert into pile

    moveCardToPile(&card1, C1);
    printf("%s \n", message); //message after second card insert into pile

    //This tests if the movecardtopile method works for the first time
    printf("%c \n", chooseTailCardFromPile(*C1)->suit);


    //removeCardFromPile(C1); //removing last remaining card from pile
    //printf("C1 head should not exist: %c", C1->head->number);

    removeCardFromPile(C1); //removing last added card from pile
    printf("%s \n", message);
    removeCardFromPile(C1); //removing last card remaining in the pile
    printf("%s \n", message);
    removeCardFromPile(C1); //removing last card remaining in the pile
    printf("%s \n", message); //This should say empty file

    return 0;
}


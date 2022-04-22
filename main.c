#include <stdio.h>

typedef struct CardNode Card;
typedef struct PileNode Pile;

struct CardNode {
    Card *next;
    Card *prev;
    char number;
    char suit;
};

// Initializing all the columns and foundations to contain NULL.
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

struct PileNode {
    Card *head;
    Card *tail;
    Pile *next;
    Pile *prev;
    int sizeOfPile;
};

int addCard(Card *newCard, Card **list);
void printBoard(Card *C1, Card *C2, Card *C3, Card *C4, Card *C5, Card *C6, Card *C7, Card *F1, Card *F2, Card *F3, Card *F4);
void distributeCards();

Pile *pileHead = NULL;
Pile *pileTail = NULL;

// Console variables
char input[64];
char message[256] = "HELLO";
char lastCom[64] = "NONE";

int main() {
    Card card = {NULL,NULL,'2','H'};
    Card card1 = {NULL,NULL,'3','K'};
    Card card2 = {NULL, NULL, '4', 'P'};


    addCard(&card, &C1);
    addCard(&card1, &C1);
    addCard(&card2, &C1);

    printBoard(C1, C2, C3, C4, C5, C6, C7, F1, F2, F3, F4);

    // printf("%c", C1->suit);
    // printf("\n" "%c", C1->next->suit);
    // printf("\n" "%c", C1->next->next->suit);

    return 0;
}


int addCard(Card *newCard, Card **list) {
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

void printBoard(Card *C1, Card *C2, Card *C3, Card *C4, Card *C5, Card *C6, Card *C7, Card *F1, Card *F2, Card *F3, Card *F4) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");

    Pile *P1, Cx;
    Card *pile = NULL;

    // P1 = pileHead->next->next->next->next->next->next;


    printf("\nLAST Command: %s\n", lastCom);
    printf("Message: %s\n", message);
    printf("INPUT > ");
}

/*
 * This function is used to separate a pile of cards onto the board by splitting the deck into 7 piles
 * representing columns.
 */
void distributeCards() {

}







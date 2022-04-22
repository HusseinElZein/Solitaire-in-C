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

Pile *pileHead = NULL;
Pile *pileTail = NULL;

// Initial variables for the console. These will be modified.
char input[64];
char message[256] = "HELLO";
char lastCommand[64] = "NONE";

int addCard(Card *newCard, Card **list);
void printBoard();
void distributeCards();

int main() {
    Card card = {NULL,NULL,'2','H'};
    Card card1 = {NULL,NULL,'3','K'};
    Card card2 = {NULL, NULL, '4', 'P'};


    addCard(&card, &C1);
    addCard(&card1, &C1);
    addCard(&card2, &C1);

    printBoard();

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

void printBoard() {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");

    Pile *P1, Cx;
    Card *tempCard = NULL;

    int column = 0;
    int row = 0;

    // P1 = pileHead->next->next->next->next->next->next;

    while (1) {     // While (1) is another word for while true.

        /* Here we are printing the content of the Card nodes. If they are empty, a "." will be printed.
         * If they contain something we print the number and suit of that particular card node. */
        if (tempCard == NULL) {
            printf(".");
            column++;
        } else {

        }

        printf("\t");

        if (column == 7) {
            printf("\n");
            column = 0;
            row++;
        }

        if (row == 6) {
            break;
        }
    }

    printf("\nLAST Command: %s\n", lastCommand);
    printf("Message: %s\n", message);
    printf("INPUT > ");
}

/*
 * This function is used to separate a pile of cards onto the board by splitting the deck into 7 piles
 * representing columns.
 */
void distributeCards() {

}







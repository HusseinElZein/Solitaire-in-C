#include <stdio.h>

typedef struct CardNode Card;
typedef struct PileNode Pile;

typedef struct CardNode Card;

struct CardNode{
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
void scanForInput();
void inputCommand(char command[]);
void simpleAdder(char command[]);






int main() {


    printBoard();

    scanForInput();

    return 0;
}


void scanForInput(){
    char str[20];
    scanf("%s", str);

    //simpleAdder(str);

    printf("You wrote %s" "\n", str);
}

void moveCard(Card **Fromlist, Card **Tolist){

}


/*void simpleAdder(char command[]){
    if(command[0] == 'C'){

        switch (command[1]) {
            case 1:

        }

    }
}
 */



void inputCommand(char command[]){
    if(command[0] == 'C'){

        if(command[1] < 8 && command[1] > 0) {

            if (command[2] == ':') {

            } else if(command[2] == '-' && command[3] == '>' || command[5] == '-' && command[6] == '>') {

            } else {

            }
        }else{
            //Error
        }

    }

    if(command[0] == 'F'){
        if(command[1] < 5 && command[1] > 0) {

            if(command[2] == '-' && command[3] == '>'){

            }
        }
    }
}


int addCard(Card *newCard, Card **list){

    Card *current = *list;

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







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

//Declaring all the methods
Card* chooseTailCardFromPile(Pile pile);
void removeCardFromPile(Pile *pile);
void moveCard(char commands[], Pile *fromPile, Pile *toPile);
void moveCardToPile(Card *cardMoved, Pile *pile);
char canBeMoved(char numberOfCardMoved);
void initPiles();
Pile selectFromPile(char command[]);
Pile selectToPile(char command[]);
Pile selectSeveralToPile(char command[]);


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

//This either removes a bottom card from one pile and adds it to the other
//Or it removes a certain amount of cards from one pile to another
/*void moveCard(char commands[], Pile *fromPile, Pile *toPile) {

    char c3 = commands[3];

    if ((commands[0] == 'C' || commands[0] == 'F')
        && commands[2] == '-' && commands[3] == '>' &&
        (commands[4] == 'C' || commands[4] == 'F')) {

        Card *card = chooseTailCardFromPile(*fromPile);
        removeCardFromPile(*fromPile);
        moveCardToPile(card, toPile);

    } else if (commands[0] == 'C' && commands[2] == ':'
               && commands[5] == '-' && commands[6] == '>'
               && commands[7] == 'C') {

        Card *chosenCard = chooseFromSpecificCardInColumn(commands[4], commands[3], selectFromPile(commands));
        if (chosenCard != null) {
            moveCardsToPile(chosenCard, selectSeveralToPile(commands));
            strcpy(message, "OK");
        } else {
            strcpy(message, "card not found");
        }
    } else {
        strcpy(message, "error in command");
    }
}
 */

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
// Initializing all the columns and foundations to contain NULL.
Pile *C1 = NULL;
Pile *C2 = NULL;
Pile *C3 = NULL;
Pile *C4 = NULL;
Pile *C5 = NULL;
Pile *C6 = NULL;
Pile *C7 = NULL;

Pile *F1 = NULL;
Pile *F2 = NULL;
Pile *F3 = NULL;
Pile *F4 = NULL;

void initPiles(){
    C1 = malloc(sizeof(Pile));
    C1->sizeOfPile = 0;
    C1->tail = NULL;
    C1->head = NULL;

    C2 = malloc(sizeof(Pile));
    C2->sizeOfPile = 0;
    C2->tail = NULL;
    C2->head = NULL;

    C3 = malloc(sizeof(Pile));
    C3->sizeOfPile = 0;
    C3->tail = NULL;
    C3->head = NULL;

    C4 = malloc(sizeof(Pile));
    C4->sizeOfPile = 0;
    C4->tail = NULL;
    C4->head = NULL;

    C5 = malloc(sizeof(Pile));
    C5->sizeOfPile = 0;
    C5->tail = NULL;
    C5->head = NULL;

    C6 = malloc(sizeof(Pile));
    C6->sizeOfPile = 0;
    C6->tail = NULL;
    C6->head = NULL;

    C7 = malloc(sizeof(Pile));
    C7->sizeOfPile = 0;
    C7->tail = NULL;
    C7->head = NULL;

    F1 = malloc(sizeof(Pile));
    F1->sizeOfPile = 0;
    F1->tail = NULL;
    F1->head = NULL;

    F2 = malloc(sizeof(Pile));
    F2->sizeOfPile = 0;
    F2->tail = NULL;
    F2->head = NULL;

    F3 = malloc(sizeof(Pile));
    F3->sizeOfPile = 0;
    F3->tail = NULL;
    F3->head = NULL;

    F4 = malloc(sizeof(Pile));
    F4->sizeOfPile = 0;
    F4->tail = NULL;
    F4->head = NULL;
}



//This returns the pile that the user wants to select a card from
Pile selectFromPile(char command[]) {

    Pile *chosenPile = NULL;

    if (command[0] == 'C') {
        switch (command[1]) {
            case '1':
                chosenPile = C1;
                break;
            case '2':
                chosenPile = C2;
                break;
            case '3':
                chosenPile = C3;
                break;
            case '4':
                chosenPile = C4;
                break;
            case '5':
                chosenPile = C5;
                break;
            case '6':
                chosenPile = C6;
                break;
            case '7':
                chosenPile = C7;
                break;
        }
    } else if (command[0] == 'F') {
        switch (command[1]) {
            case '1':
                chosenPile = F1;
                break;
            case '2':
                chosenPile = F2;
                break;
            case '3':
                chosenPile = F3;
                break;
            case '4':
                chosenPile = F4;
                break;
        }
    }
    return *chosenPile;
}

//This returns the pile that the user wants to select a card to
Pile selectToPile(char command[]) {

    Pile *chosenPile = NULL;

    if (command[4] == 'C') {
        switch (command[5]) {
            case '1':
                chosenPile = C1;
                break;
            case '2':
                chosenPile = C2;
                break;
            case '3':
                chosenPile = C3;
                break;
            case '4':
                chosenPile = C4;
                break;
            case '5':
                chosenPile = C5;
                break;
            case '6':
                chosenPile = C6;
                break;
            case '7':
                chosenPile = C7;
                break;
        }
    } else if (command[4] == 'F') {
        switch (command[5]) {
            case '1':
                chosenPile = F1;
                break;
            case '2':
                chosenPile = F2;
                break;
            case '3':
                chosenPile = F3;
                break;
            case '4':
                chosenPile = F4;
                break;
        }
    }
    return *chosenPile;
}

//This returns the pile when user has entered a specific card from a specific pile (longer input)
Pile selectSeveralToPile(char command[]) {

    Pile *chosenPile = NULL;

    if (command[7] == 'C') {
        switch (command[8]) {
            case '1':
                chosenPile = C1;
                break;
            case '2':
                chosenPile = C2;
                break;
            case '3':
                chosenPile = C3;
                break;
            case '4':
                chosenPile = C4;
                break;
            case '5':
                chosenPile = C5;
                break;
            case '6':
                chosenPile = C6;
                break;
            case '7':
                chosenPile = C7;
                break;
        }
    } else if (command[7] == 'F') {
        switch (command[8]) {
            case '1':
                chosenPile = F1;
                break;
            case '2':
                chosenPile = F2;
                break;
            case '3':
                chosenPile = F3;
                break;
            case '4':
                chosenPile = F4;
                break;
        }
    }
    return *chosenPile;
}





int main(){

    /**This tests out initializing piles, then selecting them through a char command**/
    /*Card card = {NULL, NULL, '2', 'H', '0'};
    initPiles();
    char command[] = "C1";

    moveCardToPile(&card, C1);

    printf("%c",selectFromPile(command).tail->suit); //This should say 'H'
     */




    /**Inserting two cards with moveCardToPile method**/
    /*Card card = {NULL, NULL, '2', 'H', '0'};

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


    removeCardFromPile(C1); //removing last added card from pile
    printf("%s \n", message);
    removeCardFromPile(C1); //removing last card remaining in the pile
    printf("%s \n", message);
    removeCardFromPile(C1); //removing last card remaining in the pile
    printf("%s \n", message); //This should say empty file
    */




    /**Inserting into a pile one time**/
    /*Pile *C1 = malloc(sizeof(Pile));
    C1->tail = NULL;
    Card card = {NULL,NULL,'2','H','0'};

    C1->tail = &card;

    printf("%c",chooseTailCardFromPile(*C1)->suit);
    */


    return 0;
}
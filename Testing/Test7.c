#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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


//This returns the pile that the user wants to select a card from
Pile* selectFromPile(char command[]) {

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
    return chosenPile;
}

//This returns the pile that the user wants to select a card to
Pile* selectToPile(char command[]) {

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
    return chosenPile;
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

int i;

//This chooses a specific card from a specific pile
Card* chooseFromSpecificCardInColumn(char cardSuit, char number, Pile *pile) {

    Card *chosenCard = NULL;

    Card *current = pile->tail;
    i = 1;

    //May be buggy, and's (&&) do ignore each other for some reason
    while (current->suit != cardSuit && current->number != number && i < pile->sizeOfPile) {
        current = current->prev;
        i++;
    }

    if (current->suit == cardSuit && current->number == number) {
        chosenCard = current;

        if (current->prev != NULL) {
            Card *beforeCurrent = current->prev;
            beforeCurrent->next = NULL;
            pile->tail = beforeCurrent;
            pile->tail->isHidden = 0;
        }else{
            pile->tail = NULL;
            pile->head = NULL;
        }
        pile->sizeOfPile -= i;
        strcpy(message, "OK");
    } else {
        strcpy(message, "error, card not found");
    }
    return chosenCard;
}

//This moves several cards from one pile to another pile
void moveCardsToPile(Card *cardMoved, Pile *pile) {

    Card *lastCard = cardMoved;

    while (lastCard->next != NULL) {
        lastCard = lastCard->next;
    }

    if (pile->sizeOfPile == 0) {
        pile->head = cardMoved;
        pile->tail = cardMoved;
        pile->sizeOfPile++;
        return;
    }

    if (pile->tail != NULL && cardMoved->suit != pile->tail->suit
        && canBeMoved(cardMoved->number) == pile->tail->number) {
        pile->tail->next = cardMoved;
        cardMoved->prev = pile->tail;
        pile->tail = lastCard;
        pile->sizeOfPile += i;
        strcpy(message, "OK");
    } else {
        strcpy(message, "error, cards cannot be moved");
    }
}

//This returns the pile when user has entered a specific card from a specific pile (longer input)
Pile* selectSeveralToPile(char command[]) {

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
    return chosenPile;
}

void moveCard(char commands[]) {

    if ((commands[0] == 'C' || commands[0] == 'F')
        && commands[2] == '-' && commands[3] == '>' &&
        (commands[4] == 'C' || commands[4] == 'F')) {

        Card *card = chooseTailCardFromPile(*selectFromPile(commands));
        removeCardFromPile(selectFromPile(commands));
        moveCardToPile(card, selectToPile(commands));

    } else if (commands[0] == 'C' && commands[2] == ':'
               && commands[5] == '-' && commands[6] == '>'
               && commands[7] == 'C') {

        Card *chosenCard = chooseFromSpecificCardInColumn(commands[4], commands[3], selectFromPile(commands));
        if (chosenCard != NULL) {
            moveCardsToPile(chosenCard, selectSeveralToPile(commands));
            strcpy(message, "OK");
        } else {
            strcpy(message, "card not found");
        }
    } else {
        strcpy(message, "error in command");
    }
}


int main() {

    /**This tests if the following command works "C2->C1", the method used is MoveCard which contains
     *all the necessary logic in order to move a card**/
    Card card = {NULL, NULL, '2', 'H', '0'};
    Card card1 = {NULL, NULL, 'A', 'S', '0'};

    initPiles();

    moveCardToPile(&card, C1);
    moveCardToPile(&card1, C2);

    char command[] = "C2->C1";

    printf("Bottom of C1 before moveCard: %c%c\n", C1->tail->number, C1->tail->suit);

    moveCard(command);

    printf("%s \n", message); //Should say OK!

    printf("Bottom of C1 after moveCard: %c%c", C1->tail->number, C1->tail->suit);

    return 0;
}

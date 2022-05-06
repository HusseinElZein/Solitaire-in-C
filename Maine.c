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

//Declaring all the methods
Card* chooseTailCardFromPile(Pile pile);
void removeCardFromPile(Pile *pile);
void moveCard(char commands[]);
void moveCardToPile(Card *cardMoved, Pile *pile);
char canBeMoved(char numberOfCardMoved);
void initPiles();
Pile* selectFromPile(char command[]);
Pile* selectToPile(char command[]);
Pile* selectSeveralToPile(char command[]);
void startAdding(Card *cardMoved, Pile *pile);
void moveCardsToPile(Card *cardMoved, Pile *pile);
Card* chooseFromSpecificCardInColumn(char cardSuit, char number, Pile *pile);
void addInShuffledCardsIntoColumn(char shuffledCards[]);
FILE LD(char openFileCommand[]);


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

//This function is used at the start of the game when adding cards into piles from the txt file
void startAdding(Card *cardMoved, Pile *pile) {

    if (pile->sizeOfPile == 0) {
        pile->head = cardMoved;
        pile->tail = cardMoved;
        pile->sizeOfPile++;
        return;
    }

    if (pile->tail != NULL) {
        cardMoved->prev = pile->tail;
        cardMoved->next = NULL;
        pile->tail->next = cardMoved;
        pile->tail = cardMoved;
        pile->sizeOfPile++;
    }
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

void addInShuffledCardsIntoColumn(char shuffledCards[]) {

    for (int j = 0; j < sizeof(shuffledCards); j += 2) {
        Card card = {NULL, NULL, NULL, NULL, NULL};
        card.number = shuffledCards[j];
        card.suit = shuffledCards[j + 1];

        int k = j / 2;

        if (k == 0) {
            startAdding(&card, C1);
        }
        if (k > 0 && k < 7) {
            if (k == 1) {
                card.isHidden = 1;
            }
            startAdding(&card, C2);
        }
        if (k > 6 && k < 14) {
            if (k == 7 || k == 8) {
                card.isHidden = 1;
            }
            startAdding(&card, C3);
        }
        if (k > 13 && k < 22) {
            if (k == 14 || k == 15 || k == 16) {
                card.isHidden = 1;
            }
            startAdding(&card, C4);
        }
        if (k > 21 && k < 31) {

            if (k == 22 || k == 23 || k == 24 || k == 25) {
                card.isHidden = 1;
            }
            startAdding(&card, C5);
        }
        if (k > 30 && k < 41) {

            if (k == 31 || k == 32 || k == 33 || k == 34 || k == 35) {
                card.isHidden = 1;
            }
            startAdding(&card, C6);
        }
        if (k > 40 && k < 52) {
            if (k == 41 || k == 42 || k == 43 || k == 44 || k == 45 || k == 46) {
                card.isHidden = 1;
            }
            startAdding(&card, C7);
        }
    }
}

static void printBoard() {

    printf("C1" "\t" "\t" "C2" "\t" "\t" "C3" "\t" "\t"  "C4" "\t"  "\t" "C5" "\t" "\t" "C6" "\t" "\t" "C7");

    Card *trackOfC1 = C1->head;
    Card *trackOfC2 = C2->head;
    Card *trackOfC3 = C3->head;
    Card *trackOfC4 = C4->head;
    Card *trackOfC5 = C5->head;
    Card *trackOfC6 = C6->head;
    Card *trackOfC7 = C7->head;

    bool done = false;

    while (!done) {

        if (trackOfC1 != NULL) {
            printf("%c%c""\t""\t", trackOfC1->number, trackOfC1->suit);
            trackOfC1 = trackOfC1->next;
        } else {
            printf("\t""\t");
        }

        if (trackOfC2 != NULL) {

            if (trackOfC2->isHidden == 1) {
                printf("[]" "\t" "\t");
            } else {
                printf("%c%c""\t""\t", trackOfC2->number, trackOfC2->suit);
            }
            trackOfC2 = trackOfC2->next;
        } else {
            printf("\t""\t");
        }

        if (trackOfC3 != NULL) {

            if (trackOfC3->isHidden == 1) {
                printf("[]" "\t" "\t");
            } else {
                printf("%c%c""\t""\t", trackOfC3->number, trackOfC3->suit);
            }
            trackOfC3 = trackOfC3->next;
        } else {
            printf("\t""\t");
        }

        if (trackOfC4 != NULL) {

            if (trackOfC4->isHidden == 1) {
                printf("[]" "\t" "\t");
            } else {
                printf("%c%c""\t""\t", trackOfC4->number, trackOfC4->suit);
            }
            trackOfC4 = trackOfC4->next;
        } else {
            printf("\t""\t");
        }

        if (trackOfC5 != NULL) {

            if (trackOfC5->isHidden == 1) {
                printf("[]" "\t" "\t");
            } else {
                printf("%c%c""\t""\t", trackOfC5->number, trackOfC5->suit);
            }
            trackOfC5 = trackOfC5->next;
        } else {
            printf("\t""\t");
        }

        if (trackOfC6 != NULL) {

            if (trackOfC6->isHidden == 1) {
                printf("[]" "\t" "\t");
            } else {
                printf("%c%c""\t""\t", trackOfC6->number, trackOfC6->suit);
            }
            trackOfC6 = trackOfC6->next;
        } else {
            printf("\t""\t");
        }

        if (trackOfC7 != NULL) {

            if (trackOfC7->isHidden == 1) {
                printf("[]" "\t" "\t");
            } else {
                printf("%c%c""\t""\t", trackOfC7->number, trackOfC7->suit);
            }
            trackOfC7 = trackOfC7->next;
        } else {
            printf("\t""\t");
        }

        printf("\n");

        if (trackOfC1 == NULL && trackOfC2 == NULL && trackOfC3 == NULL && trackOfC4 == NULL
            && trackOfC5 == NULL && trackOfC6 == NULL && trackOfC7 == NULL) {
            done = true;
        }

    }
}

FILE LD(char openFileCommand[]){

    FILE *pF = fopen("Cards.txt", "r");
    char buffer[255];

    if(pF == NULL) {
        printf("Unable to open file! Now opening standard file Cards.txt\n");
    } else {
        while(fgets(buffer, 255, pF) != NULL) {
            printf("%s", buffer);
        }
    }
    fclose(pF);
}








int main(){

    char openCardCommand[] = "";

    LD(openCardCommand);

    /**This tests if the following command works "C2->C1", the method used is MoveCard which contains
     *all the necessary logic in order to move a card**/
    /*Card card = {NULL, NULL, '2', 'H', '0'};
    Card card1 = {NULL, NULL, 'A', 'S', '0'};

    initPiles();

    moveCardToPile(&card, C1);
    moveCardToPile(&card1, C2);

    char command[] = "C2->C1";

    printf("Bottom of C1 before moveCard: %c\n", C1->tail->suit);

    moveCard(command, selectFromPile(command), selectToPile(command));

    printf("%s \n", message); //Should say OK!

    printf("Bottom of C1 after moveCard: %c", C1->tail->suit);
    */

    /**This tests if the following command works "C2:2C->C1", the method used is MoveCard which contains
     *all the necessary logic in order to move a card**/
    /*Card card = {NULL, NULL, '3', 'H', '0'};
    Card card1 = {NULL, NULL, '2', 'C', '0'};
    Card card2 = {NULL, NULL, 'A', 'S', '0'};

    initPiles();

    moveCardToPile(&card, C1);
    moveCardToPile(&card1, C2);
    moveCardToPile(&card2, C2);

    char command[] = "C2:2C->C1";

    printf("Bottom of C1 before moveCard: %c%c\n", C1->tail->number, C1->tail->suit);

    moveCard(command);

    printf("%s \n", message); //Should say OK!

    //printf("C2 head: %c%c\n", C2->head->number, C2->head->suit); //This should not exist
    printf("C2 size %d\n", C2->sizeOfPile); //Should be 0

    printf("One above of C1 after moveCard: %c%c\n", C1->tail->prev->number, C1->tail->prev->suit);

    printf("Bottom of C1 after moveCard: %c%c\n", C1->tail->number, C1->tail->suit);
     */


    /**This tests out the following command "C2->C1", and whether the head still exists if there was only
     * one card before moving it from a pile**/
    /*Card card = {NULL, NULL, '3', 'H', '0'};
    Card card1 = {NULL, NULL, '2', 'C', '0'};

    initPiles();

    moveCardToPile(&card, C1);
    moveCardToPile(&card1, C2);

    char command[] = "C2->C1";

    moveCard(command);

    printf("%c", C2->head->number);
    */



    /**This tests out initializing piles, then selecting them through a char command**/
    /*Card card = {NULL, NULL, '2', 'H', '0'};
    initPiles();
    char command[] = "C1";

    moveCardToPile(&card, C1);

    printf("%c",selectFromPile(command)->tail->suit); //This should say 'H'
    */





    /**Inserting two cards with moveCardToPile method, then removing them**/
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



    //removeCardFromPile(C1); //removing last remaining card from pile
    //printf("C1 head should not exist: %c", C1->head->number);

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
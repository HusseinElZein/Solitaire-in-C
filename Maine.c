#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


typedef struct CardNode Card;
typedef struct PileNode Pile;

struct CardNode{
    Card *next;
    Card *prev;
    char number;
    char suit;
    int isHidden;
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
void removeCardFromPile(Pile *pile, Pile *toPile);
void moveCard(char commands[]);
void moveCardToPile(Card *cardMoved, Pile *pile);
char canBeMoved(char numberOfCardMoved);
void initPiles();
Pile* selectFromPile(char command[]);
Pile* selectToPile(char command[]);
Pile* selectSeveralToPile(char command[]);
void startAdding(Card *cardMoved, Pile *pile);
void moveCardsToPile(Card *cardMoved, Pile *pile);
Card* chooseFromSpecificCardInColumn(char cardSuit, char number, Pile *pile, Pile *toPile);
void addInShuffledCardsIntoColumn(char shuffledCards[]);
void LD(char openFileCommand[]);
void readIntoArray(FILE *pF);
void printBoard();
void SI(char allCards[]);
void SR(char allCards[]);
int getRandomNumber(int min, int max);
char canBeMovedToFoundation(char numberOfCardMoved);
void moveCardToFoundation(Card *cardMoved, Pile *pile);


//This returns the tail of a given pile
Card* chooseTailCardFromPile(Pile pile) {
    return pile.tail;
}

bool cardCanMoveFirstIf = true;
//This removes the tail from a given pile
void removeCardFromPile(Pile *pile, Pile *toPile) {

    if(toPile->sizeOfPile == 0){
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
            return;
        }
        pile->sizeOfPile--;
    }

    if(toPile->sizeOfPile > 0) {
        if (pile->tail->suit != toPile->tail->suit
            && canBeMoved(pile->tail->number) == toPile->tail->number) {

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
                return;
            }
            pile->sizeOfPile--;
        } else {
            strcpy(message, "Card of given pile cannot be moved");
            cardCanMoveFirstIf = false;
        }
    }
}

void removeCardFromPileToFoundation(Pile *pile, Pile *toPile) {

    if(toPile->sizeOfPile == 0){
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
            return;
        }
        pile->sizeOfPile--;
        return;
    }

    if(toPile->sizeOfPile > 0) {
        if (pile->tail->suit == toPile->tail->suit
            && canBeMovedToFoundation(pile->tail->number) == toPile->tail->number) {
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
                return;
            }
            pile->sizeOfPile--;
        }
    }
}

bool bottomCard = false;
bool cardCanMove = true;


//This either removes a bottom card from one pile and adds it to the other
//Or it removes a certain amount of cards from one pile to another
void moveCard(char commands[]) {

    //Checking if can be moved from a column or foundation only into a column
    if ((commands[0] == 'C' || commands[0] == 'F')
        && commands[2] == '-' && commands[3] == '>' &&
        commands[4] == 'C') {

        Card *card = chooseTailCardFromPile(*selectFromPile(commands));
        if(card != NULL) {
            if (card->number == 'K' || (selectToPile(commands)->sizeOfPile > 0)) {
                if (cardCanMoveFirstIf) {
                    removeCardFromPile(selectFromPile(commands), selectToPile(commands));
                    moveCardToPile(card, selectToPile(commands));
                } else {
                    cardCanMoveFirstIf = true;
                }
            } else {
                strcpy(message, "Card cannot be moved to empty column if it is not a King");
            }
        }else{
            strcpy(message, "Card does not exist");
        }

    }else if((commands[0] == 'C' || commands[0] == 'F')
             && commands[2] == '-' && commands[3] == '>' &&
             commands[4] == 'F') {

        Card *card = chooseTailCardFromPile(*selectFromPile(commands));

        if (card != NULL) {
            removeCardFromPileToFoundation(selectFromPile(commands), selectToPile(commands));
            moveCardToFoundation(card, selectToPile(commands));
        }else{
            strcpy(message, "Card does not exist");
        }


    }else if (commands[0] == 'C' && commands[2] == ':'
               && commands[5] == '-' && commands[6] == '>'
               && commands[7] == 'C') {

        Card *chosenCard = chooseFromSpecificCardInColumn(commands[4], commands[3], selectFromPile(commands),
                                                          selectSeveralToPile(commands));

        if (chosenCard->number != '\0') {
            if (selectSeveralToPile(commands)->sizeOfPile > 0) {

                if (chosenCard->isHidden == 0) {
                    if (!bottomCard) {
                        if (cardCanMove) {
                            moveCardsToPile(chosenCard, selectSeveralToPile(commands));
                            strcpy(message, "OK");
                        } else {
                            cardCanMove = true;
                        }
                    } else {
                        bottomCard = false;
                        strcpy(message, "Choose another way to move a bottom card");
                    }
                } else {
                    strcpy(message, "card is hidden and can therefore not be moved");
                }
            } else {
                strcpy(message, "You can only move one card at a time to an empty column");
            }
        }else{
            strcpy(message, "Specific card does not exist or is hidden");
        }
    }else {
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

//This moves one card to the bottom of a foundation
void moveCardToFoundation(Card *cardMoved, Pile *pile) {

    if (pile->sizeOfPile == 0) {

        if (cardMoved->number == 'A') {
            pile->head = cardMoved;
            pile->tail = cardMoved;
            pile->sizeOfPile++;
            strcpy(message, "OK");
            return;
        } else {
            strcpy(message, "Card is not an A, therefore cannot be moved to foundation");
            return;
        }
    }

        if (pile->tail != NULL && cardMoved->suit == pile->tail->suit
            && canBeMovedToFoundation(cardMoved->number) == pile->tail->number) {
            cardMoved->prev = pile->tail;
            cardMoved->next = NULL;
            pile->tail->next = cardMoved;
            pile->tail = cardMoved;
            pile->sizeOfPile++;
            strcpy(message, "OK, card moved");
        } else {
            strcpy(message, "error, card cannot be moved to foundation");
        }
    }

//This returns the next card number in the hierachy
char canBeMovedToFoundation(char numberOfCardMoved){

    switch (numberOfCardMoved) {
        case '2': return 'A';
        case '3': return '2';
        case '4': return '3';
        case '5': return '4';
        case '6': return '5';
        case '7': return '6';
        case '8': return '7';
        case '9': return '8';
        case 'T': return '9';
        case 'J': return 'T';
        case 'Q': return 'J';
        case 'K': return 'Q';
        default: return '0';
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
Card* chooseFromSpecificCardInColumn(char cardSuit, char number, Pile *pile, Pile *toPile) {

    Card *chosenCard = malloc(sizeof(Card));
    chosenCard->isHidden = 0;
    chosenCard->number = '\0';
    chosenCard->suit = '\0';
    chosenCard->next = NULL;
    chosenCard->prev = NULL;

    Card *current = pile->tail;
    i = 1;


    while ((current->suit != cardSuit || current->number != number) && i < pile->sizeOfPile) {
        current = current->prev;
        i++;
    }
    if(i == 1){
        bottomCard = true;
    }

    if(toPile->sizeOfPile > 0){
        if (current->suit == cardSuit && current->number == number && i != 1) {
            if (current->isHidden != 1) {
                chosenCard = current;
                chosenCard->isHidden = current->isHidden;

                if (current->prev != NULL) {
                    Card *beforeCurrent = current->prev;
                    beforeCurrent->next = NULL;
                    pile->tail = beforeCurrent;
                    pile->tail->isHidden = 0;
                } else {
                    pile->tail = NULL;
                    pile->head = NULL;
                }
                pile->sizeOfPile -= i;
                strcpy(message, "OK");
            } else {
                strcpy(message, "Card is hidden and can therefore not be moved");
            }
        } else {
            cardCanMove = false;
            strcpy(message, "Error, specific card cannot be moved");
        }
    } else {
        strcpy(message, "Error, you cannot move several cards to an empty column");
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

    for (int j = 0; j < 104; j += 2) {
        Card *card = malloc(sizeof(Card));
        card->isHidden = 0;
        card->suit = '\0';
        card->number = '\0';
        card->next = NULL;
        card->prev = NULL;


        card->number = shuffledCards[j];
        card->suit = shuffledCards[j + 1];

        int k = j / 2;

        if (k == 0) {
            startAdding(card, C1);
        }
        if (k > 0 && k < 7) {
            if (k == 1) {
                card->isHidden = 1;
            }
            startAdding(card, C2);
        }
        if (k > 6 && k < 14) {
            if (k == 7 || k == 8) {
                card->isHidden = 1;
            }
            startAdding(card, C3);
        }
        if (k > 13 && k < 22) {
            if (k == 14 || k == 15 || k == 16) {
                card->isHidden = 1;
            }
            startAdding(card, C4);
        }
        if (k > 21 && k < 31) {

            if (k == 22 || k == 23 || k == 24 || k == 25) {
                card->isHidden = 1;
            }
            startAdding(card, C5);
        }
        if (k > 30 && k < 41) {

            if (k == 31 || k == 32 || k == 33 || k == 34 || k == 35) {
                card->isHidden = 1;
            }
            startAdding(card, C6);
        }
        if (k > 40 && k < 52) {
            if (k == 41 || k == 42 || k == 43 || k == 44 || k == 45 || k == 46) {
                card->isHidden = 1;
            }
            startAdding(card, C7);
        }
    }
}

void printBoard() {

    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\tF1\tF2\tF3\tF4\n");

    Card *trackOfC1 = C1->head;
    Card *trackOfC2 = C2->head;
    Card *trackOfC3 = C3->head;
    Card *trackOfC4 = C4->head;
    Card *trackOfC5 = C5->head;
    Card *trackOfC6 = C6->head;
    Card *trackOfC7 = C7->head;

    Card *F1tail = F1->tail;
    Card *F2tail = F2->tail;
    Card *F3tail = F3->tail;
    Card *F4tail = F4->tail;

    bool done = false;
    bool foundationsPrinted = false;

    while (!done) {

        if (trackOfC1 != NULL) {
            printf("%c%c\t", trackOfC1->number, trackOfC1->suit);
            trackOfC1 = trackOfC1->next;
        } else {
            printf("\t");
        }

        if (trackOfC2 != NULL) {

            if (trackOfC2->isHidden == 1) {
                printf("[]\t");
            } else {
                printf("%c%c\t", trackOfC2->number, trackOfC2->suit);
            }
            trackOfC2 = trackOfC2->next;
        } else {
            printf("\t");
        }

        if (trackOfC3 != NULL) {

            if (trackOfC3->isHidden == 1) {
                printf("[]\t");
            } else {
                printf("%c%c\t", trackOfC3->number, trackOfC3->suit);
            }
            trackOfC3 = trackOfC3->next;
        } else {
            printf("\t");
        }

        if (trackOfC4 != NULL) {

            if (trackOfC4->isHidden == 1) {
                printf("[]\t");
            } else {
                printf("%c%c\t", trackOfC4->number, trackOfC4->suit);
            }
            trackOfC4 = trackOfC4->next;
        } else {
            printf("\t");
        }

        if (trackOfC5 != NULL) {

            if (trackOfC5->isHidden == 1) {
                printf("[]\t");
            } else {
                printf("%c%c\t", trackOfC5->number, trackOfC5->suit);
            }
            trackOfC5 = trackOfC5->next;
        } else {
            printf("\t");
        }

        if (trackOfC6 != NULL) {

            if (trackOfC6->isHidden == 1) {
                printf("[]\t");
            } else {
                printf("%c%c\t", trackOfC6->number, trackOfC6->suit);
            }
            trackOfC6 = trackOfC6->next;
        } else {
            printf("\t");
        }

        if (trackOfC7 != NULL) {

            if (trackOfC7->isHidden == 1) {
                printf("[]\t");
            } else {
                printf("%c%c\t", trackOfC7->number, trackOfC7->suit);
            }
            trackOfC7 = trackOfC7->next;
        } else {
            printf("\t");
        }

        if(!foundationsPrinted) {
            if (F1tail != NULL) {
                printf("%c%c\t", F1tail->number, F1tail->suit);
            } else {
                printf("[]\t");
            }

            if (F2tail != NULL) {
                printf("%c%c\t", F2tail->number, F2tail->suit);
            } else {
                printf("[]\t");
            }

            if (F3tail != NULL) {
                printf("%c%c\t", F3tail->number, F3tail->suit);
            } else {
                printf("[]\t");
            }

            if (F4tail != NULL) {
                printf("%c%c\n", F4tail->number, F4tail->suit);
            } else {
                printf("[]\n");
            }
            foundationsPrinted = true;
        }else{
            printf("\n");
        }
        if (trackOfC1 == NULL && trackOfC2 == NULL && trackOfC3 == NULL && trackOfC4 == NULL
            && trackOfC5 == NULL && trackOfC6 == NULL && trackOfC7 == NULL) {
            done = true;
        }
    }
}
bool SWused = false;

void SW() {
    strcpy(message, "Now showing all cards, to hide the cards again, type a random command");
    SWused = true;

    printf("C1\t\tC2\t\tC3\t\tC4\t\tC5\t\tC6\t\tC7\t\t\tF1\t\tF2\t\tF3\t\tF4\n");

    Card *trackOfC1 = C1->head;
    Card *trackOfC2 = C2->head;
    Card *trackOfC3 = C3->head;
    Card *trackOfC4 = C4->head;
    Card *trackOfC5 = C5->head;
    Card *trackOfC6 = C6->head;
    Card *trackOfC7 = C7->head;

    Card* F1tail = F1->tail;
    Card* F2tail = F2->tail;
    Card* F3tail = F3->tail;
    Card* F4tail = F4->tail;

    bool done = false;
    bool foundationsPrinted = false;

    while (!done) {

        if (trackOfC1 != NULL) {
            printf("%c%c\t\t", trackOfC1->number, trackOfC1->suit);
            trackOfC1 = trackOfC1->next;
        } else {
            printf("\t\t");
        }

        if (trackOfC2 != NULL) {
                printf("%c%c\t\t", trackOfC2->number, trackOfC2->suit);
                trackOfC2 = trackOfC2->next;
        } else {
            printf("\t\t");
        }

        if (trackOfC3 != NULL) {
            printf("%c%c\t\t", trackOfC3->number, trackOfC3->suit);
            trackOfC3 = trackOfC3->next;
        } else {
            printf("\t\t");
        }

        if (trackOfC4 != NULL) {
            printf("%c%c\t\t", trackOfC4->number, trackOfC4->suit);
            trackOfC4 = trackOfC4->next;
        } else {
            printf("\t\t");
        }

        if (trackOfC5 != NULL) {
            printf("%c%c\t\t", trackOfC5->number, trackOfC5->suit);
            trackOfC5 = trackOfC5->next;
        } else {
            printf("\t\t");
        }

        if (trackOfC6 != NULL) {
            printf("%c%c\t\t", trackOfC6->number, trackOfC6->suit);
            trackOfC6 = trackOfC6->next;
        } else {
            printf("\t\t");
        }

        if (trackOfC7 != NULL) {
            printf("%c%c\t\t\t", trackOfC7->number, trackOfC7->suit);
            trackOfC7 = trackOfC7->next;
        } else {
            printf("\t\t\t");
        }

        if(!foundationsPrinted) {
            if (F1tail != NULL) {
                printf("%c%c\t\t", F1tail->number, F1tail->suit);
            } else {
                printf("[]\t\t");
            }

            if (F2tail != NULL) {
                printf("%c%c\t\t", F2tail->number, F2tail->suit);
            } else {
                printf("[]\t\t");
            }

            if (F3tail != NULL) {
                printf("%c%c\t\t", F3tail->number, F3tail->suit);
            } else {
                printf("[]\t\t");
            }

            if (F4tail != NULL) {
                printf("%c%c\n", F4tail->number, F4tail->suit);
            } else {
                printf("[]\n");
            }
            foundationsPrinted = true;
        }else{
            printf("\n");
        }
        if (trackOfC1 == NULL && trackOfC2 == NULL && trackOfC3 == NULL && trackOfC4 == NULL
            && trackOfC5 == NULL && trackOfC6 == NULL && trackOfC7 == NULL) {
            done = true;
        }
    }
}

void loadGameInput(){
    printf("\nLAST Command: %s\n", lastCommand);
    printf("Message: %s\n", message);
    printf("INPUT > ");

    char str[40];
    fgets(str, sizeof(str), stdin);
    printf("\n");

    char lastly[40];

    for (int j = 0; j < 40; j++) {
        if(str[j] != '\0' && str[j] != '\n'){
            lastly[j] = str[j];
        }else{
            break;
        }
    }
    strcpy(lastCommand, lastly);

    if(str[0] == 'L' && str[1] == 'D') {

        char fileName[40];

        for (int j = 3; j < 40; j++) {
            if(str[j] != '\0'){
                fileName[j-3] = lastly[j];
            }else{
                break;
            }
        }
        LD(fileName);
    }else{
        strcpy(message, "No LD command given");
    }
}

char allCards[104];
bool writeFileName = true;

void readIntoArray(FILE *pF) {

    int lineNumber = 1;

    while(!feof(pF) && lineNumber != 105) {

        char c = fgetc(pF);
        if (c != '\n') {
            if (((c > '1' && c <= '9') || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K'
                 || c == 'C' || c == 'D' || c == 'H' || c == 'S')) {
                allCards[i] = c;
                i++;
                lineNumber++;
            } else {
                int half = lineNumber / 2;
                printf("There is an error reading your txt file at line %d\n", half);
                exit(0);
                strcpy(message, "Write a file name that does not have an error in any lines");
                return;
            }
        }
    }
    strcpy(message, "File loaded successfully, now you can shuffle with SR or SI");
    writeFileName = false;
}

void LD(char openFileCommand[]) {
    FILE *pF = fopen(openFileCommand, "r");

    if (pF == NULL) {
        printf("Unable to open file! Have you made sure to put in your txt file in the folder: cmake-build-debug ?"
               " Now opening standard file Cards.txt\n");
        writeFileName = false;

        pF = fopen("Cards.txt", "r");
        readIntoArray(pF);
    } else {
        readIntoArray(pF);
    }
    fclose(pF);
}

void SI(char allCards[]){
    char halfOne[52];
    char halfTwo[52];

    for (int j = 0; j < 52; j++) {
        halfOne[j] = allCards[j];
    }

    for (int j = 52; j < 104; j++) {
        halfTwo[j - 52] = allCards[j];
    }

    int k = 0;

    for (int j = 0; j < 52 - 1; j += 2) {
        allCards[k] = halfOne[j];
        k++;
        allCards[k] = halfOne[j + 1];
        k++;
        allCards[k] = halfTwo[j];
        k++;
        allCards[k] = halfTwo[j + 1];
        k++;
    }
    strcpy(message, "Loaded SI successfully, press P to play");
}

char shuffledCards[104];

void SR(char allCards[]){

    int checker[52];

    int random = 0;

    int k = 0, i = 0;

    bool isTheSame = true, done = false;

    srand(time(NULL));
    while (!done) {

        while (isTheSame) {

            random = getRandomNumber(-1, 104);

            for (int j = 0; j < 51; j++) {
                if (checker[j] == random) {
                    isTheSame = true;
                    break;
                } else {
                    isTheSame = false;
                }
            }
        }

        checker[i] = random;
        i++;

        shuffledCards[k] = allCards[random];
        k++;
        shuffledCards[k] = allCards[random + 1];
        k++;

        isTheSame = true;

        for (int j = 0; j < 104; j++) {

            if (shuffledCards[j] == '\0') {
                done = false;
                isTheSame = true;
                break;
            } else {
                done = true;
                isTheSame = false;
            }
        }
    }
    strcpy(message, "Loaded SR successfully, press P to play");
}

int getRandomNumber(int min, int max) {

    bool again = true;
    int random = 0;

    while (again) {

        random = rand() % max;

        if (random % 2 == 0) {
            again = false;
        }
    }
    return random;
}


bool writeP = true;

void startGame(){
    printf("\nLAST Command: %s\n", lastCommand);
    printf("Message: %s\n", message);
    printf("INPUT > ");

    char str[40];
    scanf("%s", str);
    printf("\n");

    strcpy(lastCommand, str);

    if(str[0] == 'P' && str[2] == '\0') {
        strcpy(message, "Game started");
        writeP = false;
    }else{
        strcpy(message, "Write P to start game");
    }
}

bool shuffleAgain = true;
void loadShuffleInput() {
    printf("\nLAST Command: %s\n", lastCommand);
    printf("Message: %s\n", message);
    printf("Input > ");

    char str[40];
    scanf("%s", str);
    printf("\n");

    strcpy(lastCommand, str);

    if(str[0] == 'S' && str[1] == 'I' && str[2] == '\0') {
        SI(allCards);
        addInShuffledCardsIntoColumn(allCards);
        shuffleAgain = false;
    }else if(str[0] == 'S' && str[1] == 'R' && str[2] == '\0'){
        SR(allCards);
        addInShuffledCardsIntoColumn(shuffledCards);
        shuffleAgain = false;
    }else{
        strcpy(message, "Write a valid shuffle command (SR or SI)");
    }
}

bool gameIsFinished(){
    if(C1->head == NULL && C2->head == NULL && C3->head == NULL && C4->head == NULL && C5->head == NULL
    && C6->head == NULL && C7->head == NULL){
        strcpy(message, "Congratulations, you have finished Yukon");
        return true;
    }else{
        return false;
    }
}

void QQ(){
    exit(0);
}

void Q(){
    bool done = false;
    strcpy(message, "Entered Q in play phase");

    while(!done) {
        printBoard();
        printf("\nLAST Command: %s\n", lastCommand);
        printf("Message: write QQ or P\n");
        printf("Input > ");

        char str[5];
        scanf("%s", str);
        printf("\n");

        strcpy(lastCommand, str);

        if (str[0] == 'P' && str[1] == '\0') {
            strcpy(lastCommand, str);
            done = true;
            strcpy(message, "OK");
        }else if(str[0] == 'Q' && str[1] == 'Q' && str[2] == '\0') {
            strcpy(lastCommand, str);
            done = true;
            QQ();
        }else{
            strcpy(message, "Write in QQ to quit, or P to continue playing");
        }
    }
}


int main(){

    /**This tests our getRandomNumber function to see if the numbers generated are between 0-102 and in even numbers **/
    /*for (int j = 0; j < 300; ++j) {
        printf("%d\n", getRandomNumber(-1, 104));
    }
    printf("__________________________\n\n\n\n");
     */


    /**This tests our SR function that moves cards randomly and tests SW which prints all cards**/
    /*initPiles();
    LD("Cards.txt");
    SR(allCards);
    addInShuffledCardsIntoColumn(shuffledCards);
    SW();
    printf("\n");
    printBoard();
     */

    /**This tests the logic of moving to a foundation with a valid card and a non-valid with matching card-suits
     * and the correct order of placement (From A to K)**/
    /*Card card = {NULL, NULL, '2', 'H', '0'};
    Card card1 = {NULL, NULL, 'A', 'S', '0'};

    initPiles();

    moveCardToPile(&card, C1);
    moveCardToPile(&card1, C2);

    char command[] = "C2->F1";

    printf("Board before moving to a Foundation\n");
    printBoard();

    moveCard(command);
    printf("Board after moving to a Foundation\n");
    printBoard();

    printf("\nMessage: %s \n", message); //Should say OK!

    char commandTwo[] = "C1->F1";
    moveCard(commandTwo);
    printf("Board after moving to a Foundation second time\n");
    printBoard();

    printf("\nMessage: %s \n", message); //Should say NOT OK!
     */


    /**Main code**/
    initPiles();

    //First phase, writing in a file name
    while(writeFileName){
        printBoard();
        loadGameInput();
    }
    //Second phase, writing in a shuffle command
    while(shuffleAgain){
        printBoard();
        loadShuffleInput();
    }

    //Third phase, command to start game
    while(writeP){
        printBoard();
        startGame();
    }

    //Forth; Play-phase, until player either presses Q, QQ, SW, or writes a command to move cards
    while(!gameIsFinished()) {

        if (!SWused) {
        printBoard();
        }else{
            SWused = false;
        }
        printf("\nLAST Command: %s\n", lastCommand);
        printf("Message: %s\n", message);
        printf("Input > ");

        char str[40];
        scanf("%s", str);
        printf("\n");

        strcpy(lastCommand, str);

        if(str[0] == 'C' || str[0] == 'F'){
            moveCard(str);
        }else if(str[0] == 'Q' && str[1] == 'Q' && str[2] == '\0'){
            QQ();
        }else if(str[0] == 'S' && str[1] == 'W' && str[2] == '\0'){
            SW();
        }else if(str[0] == 'Q' && str[1] == '\0') {
        Q();
        }
        else{
            strcpy(message, "Write in Q, QQ, SW, or a command to move a card");
        }
    }
    printBoard();

    /**This tests if our input of txt file works with input from the user
     * And: To check if there is no spaces in the array. And the correct deck of cards are placed**/
    /*char openCardCommand[] = "CardsWILLFAIL.txt";
    LD(openCardCommand);
    for (int j = 0; j < 104; j+=2) {
        printf("%c%c\n", allCards[j], allCards[j+1]);
    }
     */

    /**This tests if the SI method works and shuffles correctfully. This also tests our addInShuffledCardsIntoColumn
     * method, and also our print method. It overall sees if the correct pointers are placed in the columns and inside
     * printboard() method**/
    /*char openCardCommand[] = "Cards.txt";
    LD(openCardCommand);

    initPiles();

    SI(allCards);

    addInShuffledCardsIntoColumn(allCards);
    printBoard();
     */


    /**This tests if the following command works "C2->C1", the method used is moveCard which contains
     *all the necessary logic in order to move a card**/
    /*Card card = {NULL, NULL, '2', 'H', '0'};
    Card card1 = {NULL, NULL, 'A', 'S', '0'};

    initPiles();

    moveCardToPile(&card, C1);
    moveCardToPile(&card1, C2);

    char command[] = "C2->C1";

    printf("Bottom of C1 before moveCard: %c\n", C1->tail->suit);
    printf("Bottom of C2 before move %c\n", C2->tail->suit);
    //printBoard();
    //printf("\n");

    moveCard(command);

    printf("%s \n", message); //Should say OK!

    printf("Bottom of C1 after moveCard: %c\n\n", C1->tail->suit);

    //printBoard();
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
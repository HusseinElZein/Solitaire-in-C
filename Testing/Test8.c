#include <stdio.h>

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

char allCards[104];

void readIntoArray(FILE *pF) {

    int lineNumber = 1;

    for (int i = 0; i < 104; i++) {

        char c = fgetc(pF);
        if (c != '\n') {
            if (((c > '1' && c <= '9') || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K'
                 || c == 'C' || c == 'D' || c == 'H' || c == 'S')) {
                allCards[i] = c;
                i++;
                lineNumber++;
            } else {
                int half = lineNumber / 2;
                printf("There is an error reading your txt file at line %d", half);
                break;
            }
        }
    }
}

void LD(char openFileCommand[]) {
    FILE *pF = fopen(openFileCommand, "r");

    if (pF == NULL) {
        printf("Unable to open file! Have you made sure to put in your txt file in the folder: cmake-build-debug ?"
               " Now opening standard file Cards.txt\n");

        pF = fopen("Cards.txt", "r");
        readIntoArray(pF);
    } else {
        readIntoArray(pF);
    }
    fclose(pF);
}

int main() {

    /**This tests if our input of txt file works with input from the user
     * And: To check if there is no spaces in the array. And the correct deck of cards are placed**/
    char openCardCommand[] = "CardsWILLFAIL.txt";
    LD(openCardCommand);
    for (int j = 0; j < 104; j+=2) {
        printf("%c%c\n", allCards[j], allCards[j+1]);
    }

    return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printArr(char* inArr, int len);
int checkValid(
    int rangeStart, int rangeEnd,
    char checkChar, char checkArr[],
    int arrLen
);
int checkValid2(
    int rangeStart, int rangeEnd,
    char checkChar, char checkArr[]
);

int main()
{
    char password[21];
    int passLength;
    int rangeStart;
    int rangeEnd;
    char targetChar;
    int validCounter = 0;
    int validCounter2 = 0;
    int scanSuccess;
    FILE *inFptr;
    FILE *outFptr;

    inFptr = fopen("/Users/lowe/Documents/Programmering/misc_code/advent_of_code/aoc_2020/input_day2.txt", "r");

    if (inFptr == NULL) {
        printf("Error opening file");
        exit(1);
    }

    scanSuccess = fscanf(
        inFptr, "%d-%d %c: %s",
        &rangeStart,
        &rangeEnd,
        &targetChar,
        password
    );

    while(scanSuccess != EOF) {
        passLength = strlen(password);
        validCounter += checkValid(
            rangeStart, rangeEnd, targetChar,
            password, passLength
        );
        validCounter2 += checkValid2(
            rangeStart, rangeEnd, targetChar,
            password
        );
        scanSuccess = fscanf(
            inFptr, "%d-%d %c: %s",
            &rangeStart,
            &rangeEnd,
            &targetChar,
            password
        );
    }
    fclose(inFptr);

    outFptr = fopen("/Users/lowe/Documents/Programmering/misc_code/advent_of_code/aoc_2020/output_day2.txt", "w");
    fprintf(outFptr, "%d\n", validCounter);
    fprintf(outFptr, "%d\n", validCounter2);
    fclose(outFptr);

    return 0;
}

int checkValid(
    int rangeStart, int rangeEnd, char targetChar,
    char checkArr[], int arrLen
) {
    int numMatches = 0;
    int isValid = 0;
    for (int i = 0; i < arrLen; i++) {
        if (targetChar == checkArr[i]) {
            numMatches++;
        }
    }
    if ( (numMatches >= rangeStart) && (numMatches <= rangeEnd)) {
        isValid = 1;
    }
    return isValid;
}

int checkValid2(
    int firstPos, int secondPos, char targetChar,
    char checkArr[]
) {
    int numMatches = 0;
    int isValid = 0;
    numMatches += checkArr[firstPos-1] == targetChar;
    numMatches += checkArr[secondPos-1] == targetChar;
    if (numMatches == 1) {
        isValid = 1;
    }
    return isValid;
}

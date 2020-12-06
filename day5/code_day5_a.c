#include <stdio.h>
#include <stdlib.h>

// define constants based on exercise description/input format
# define NUM_PASSES 869
# define MIN_ROW 0
# define MAX_ROW 127
# define MIN_COL 0
# define MAX_COL 7

int solve();
void halveRange(int* rangeStart, int* rangeEnd, char halveCode);

int main() {
    int errorCode = 0;
    if (solve()) {
        errorCode = 1;
    }
    return errorCode;
}

int solve() {
    // array that will hold all boarding pass seat ID's
    int seatIds[NUM_PASSES];
    // counter for number of seat ID's that have been added so far
    int idCounter = 0;
    // variable for holding the most recently calculated seat ID
    int lastId;
    // highest seat ID
    int maxId = 0;
    // variable for storing row number once all others have been
    // eliminated
    int rowNumber;
    // boolean which indicates if the last previously scanned character
    // was related to row placement (rather than column placement)
    int lastCRow = 1;
    // boolean which indicates if the character currently being
    // processed is related to row placement
    int currentCRow;
    // value indicating whether new data were scanned, or if
    // EOF symbol was hit
    int scanResult;
    // value indicating start of range of still-not-eliminated
    // row/column numbers
    int rangeStart = MIN_ROW;
    // value indicating end of range of still-not-eliminated
    // row/column numbers
    int rangeEnd = MAX_ROW;
    // variable for holding newly scanned characters
    char currentChar;
    // input data file pointer
    FILE *inFptr;
    // output file pointer
    FILE *outFptr;

    // open connection to input file
    inFptr = fopen("input_day5.txt", "r");

    if (inFptr == NULL) {
        printf("Error opening file");
        exit(1);
    }

    scanResult = fscanf(
        inFptr, "%c",
        &currentChar
    );

    // while input file EOF hasn't been reached
    while(scanResult != EOF) {
        if (currentChar == ' ' || currentChar == '\n') {
            scanResult = fscanf(
                inFptr, "%c",
                &currentChar
            );
            continue;
        }
        // if char currently being processed is related to row placement
        if (currentChar == 'F' || currentChar == 'B') {
            currentCRow = 1;
        } else {
            currentCRow = 0;
        }
        // if char currently being processed marks the start of a new
        // row of input/pass data
        if (currentCRow == 1 && lastCRow == 0) {
            lastId = rowNumber * 8 + rangeStart;
            if (lastId > maxId) {
                maxId = lastId;
            }
            seatIds[idCounter] = lastId;
            idCounter += 1;
            rangeStart = MIN_ROW;
            rangeEnd = MAX_ROW;
        }
        // if char currently being processed marks start of column
        // placement data
        else if (currentCRow == 0 && lastCRow == 1) {
            rowNumber = rangeStart;
            rangeStart = MIN_COL;
            rangeEnd = MAX_COL;
        }
        halveRange(&rangeStart, &rangeEnd, currentChar);

        scanResult = fscanf(
            inFptr, "%c",
            &currentChar
        );
        lastCRow = currentCRow;
    }
    // handle the very last ID
    lastId = rowNumber * 8 + rangeStart;
    if (lastId > maxId) {
        maxId = lastId;
    }
    fclose(inFptr);

    outFptr = fopen("output_day5_a.txt", "w");

    fprintf(outFptr, "%d\n", maxId);
    fclose(outFptr);

    return 0;
}

void halveRange(int* startRange, int* endRange, char halveCode) {
    if (halveCode == 'F' || halveCode == 'L') {
        *endRange = (*startRange + *endRange) / 2;
    } else {
        *startRange = (*startRange + *endRange + 1) / 2;
    }
}

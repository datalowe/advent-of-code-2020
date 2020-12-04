#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define constants based on exercise description/input format
# define INPUT_COL_WIDTH 31
# define N_STEPPERS 5

// declare functions
void printArr(char * inArr, int len);
int checkTree(
    int xPos, int yPos,
    char * checkArr
);

int main()
{
    // array for reading in row-wise data to
    char readArr[INPUT_COL_WIDTH+1];
    // counter for keeping track of which row is currently being processed
    int rowCounter = 0;
    // counters for number of trees hit
    int treeCounters[N_STEPPERS] = {0, 0, 0, 0, 0};
    // array of rightward step sizes
    int rStepSizes[N_STEPPERS] = {1, 3, 5, 7, 1};
    // array of downward step sizes
    int dStepSizes[N_STEPPERS] = {1, 1, 1, 1, 2};
    // x positions of map reader heads, where 0 corresponds to far left
    int headXPos[N_STEPPERS] = {0, 0, 0, 0, 0};
    // product of tree counters after finishing counting
    unsigned long treeProduct = 1;
    // value indicating whether new data were scanned, or if
    // EOF symbol was hit
    int scanResult;
    // input data file pointer
    FILE *inFptr;
    // output file pointer
    FILE *outFptr;

    // open connection to input file
    inFptr = fopen("/Users/lowe/Documents/Programmering/misc_code/advent_of_code/aoc_2020/input_day3.txt", "r");

    if (inFptr == NULL) {
        printf("Error opening file");
        exit(1);
    }

    scanResult = fscanf(
        inFptr, "%s",
        readArr
    );

    // while input file EOF hasn't been reached
    while(scanResult != EOF) {
        for (int i = 0; i < N_STEPPERS; i++) {
            // if this row is reached by stepper (not 'jumped over'
            // due to down step size)
            if (rowCounter % dStepSizes[i] == 0) {
                // increment tree counter if current position is on tree
                treeCounters[i] += readArr[headXPos[i]] == '#';
                // in preparation for next 'non-skipped'  row,
                // move the reader head <right step size> number of positions
                // to the right, looping back to far left end when going past
                // the input's column width
                headXPos[i] = (headXPos[i] + rStepSizes[i]) % INPUT_COL_WIDTH;
            }
        }
        scanResult = fscanf(
            inFptr, "%s",
            readArr
        );
        rowCounter += 1;
    }
    fclose(inFptr);

    outFptr = fopen("/Users/lowe/Documents/Programmering/misc_code/advent_of_code/aoc_2020/output_day3_b.txt", "w");

    for (int i = 0; i < N_STEPPERS; i++) {
        treeProduct *= treeCounters[i];
    }
    fprintf(outFptr, "%lu\n", treeProduct);
    fclose(outFptr);

    return 0;
}

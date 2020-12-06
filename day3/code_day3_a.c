#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define constants based on exercise description/input format
# define INPUT_COL_WIDTH 31
# define R_STEP_SIZE 3
# define D_STEP_SIZE 1


int main()
{
    // array for reading in row-wise data to
    char readArr[INPUT_COL_WIDTH+1];
    // counter for keeping track of which row is currently being processed
    int rowCounter = 0;
    // counter for number of trees hit
    int treeCounter = 0;
    // x position of map reader head, where 0 corresponds to far left
    int headXPos = 0;
    // value indicating whether new data were scanned, or if
    // EOF symbol was hit
    int scanResult;
    // input data file pointer
    FILE *inFptr;
    // output file pointer
    FILE *outFptr;

    // open connection to input file
    inFptr = fopen("input_day3.txt", "r");

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
        // if this row is 'jumped over' due to down step size,
        // continue to the next one
        if (rowCounter % D_STEP_SIZE != 0) {
            continue;
        }
        // increment tree counter if current position is on tree
        treeCounter += readArr[headXPos] == '#';
        // in preparation for next row, move the reader head <right step size>
        // number of positions to the right, looping back to far left end
        // when going past the input's column width
        headXPos = (headXPos + R_STEP_SIZE) % INPUT_COL_WIDTH;
        scanResult = fscanf(
            inFptr, "%s",
            readArr
        );
        rowCounter += 1;
    }
    fclose(inFptr);

    outFptr = fopen("output_day3_a.txt", "w");

    fprintf(outFptr, "%d\n", treeCounter);
    fclose(outFptr);

    return 0;
}

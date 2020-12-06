#include <stdio.h>
#include <stdlib.h>

void findSumVals(int* inArr, int* outArr, int maxIndex);
void findSumVals3(int* inArr, int* outArr, int maxIndex);
int prodArr(int passArr[], int len);

int main()
{

    int nums[255];
    int numCounter = 0;
    int factorArr[2];
    int factorArr3[3];
    int factorProd;
    FILE *inFptr;
    FILE *outFptr;

    if ( (inFptr = fopen("input_day1.txt", "r")) == NULL) {
    printf("Error opening file");

    exit(1);
}


    while(!feof(inFptr)) {
        fscanf(inFptr, "%d", &nums[numCounter]);
        numCounter++;
    }

    fclose(inFptr);

    findSumVals(nums, factorArr, numCounter);

    outFptr = fopen("output_day1.txt", "w");

    factorProd = prodArr(factorArr, 2);

    fprintf(outFptr, "%d\n", factorProd);

    findSumVals3(nums, factorArr3, numCounter);

    factorProd = prodArr(factorArr3, 3);

    fprintf(outFptr, "%d\n", factorProd);

    fclose(outFptr);

    return 0;
}


void findSumVals(int inArr[], int outArr[], int maxIndex) {
    int i;
    int j;
    int iterSum;
    int foundIt = 0;
    int targetSum = 2020;
    for (i = 0; i < maxIndex - 1; i++) {
        for (j = i +1; j < maxIndex; j++) {
            iterSum = inArr[i] + inArr[j];
            if (iterSum == targetSum) {
                outArr[0] = inArr[i];
                outArr[1] = inArr[j];
                foundIt = 1;
                break;
            }
        }
        if (foundIt) {
            break;
        }
    }
}


void findSumVals3(int inArr[], int outArr[], int maxIndex) {
    int i;
    int j;
    int k;
    int iterSum;
    int foundIt = 0;
    int targetSum = 2020;
    for (i = 0; i < maxIndex - 2; i++) {
        for (j = i +1; j < maxIndex -1; j++) {
            for (k = j +1; k < maxIndex; k++) {
                iterSum = inArr[i] + inArr[j] + inArr[k];
                if (iterSum == targetSum) {
                    outArr[0] = inArr[i];
                    outArr[1] = inArr[j];
                    outArr[2] = inArr[k];
                    foundIt = 1;
                    break;
                }
            }
            if (foundIt) {
                break;
            }
        }
        if (foundIt) {
            break;
        }
    }
}

int prodArr(int passArr[], int len) {
    int product = 1;
    int i;
    for (i = 0; i < len; i++) {
        product *= passArr[i];
    }
    return product;
}

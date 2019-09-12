/***********************************************
* Author: Thomas Williams
* Date: 9/12/19
* Description: A C program will read the number 
*   of children and a number to divide into 
*   the divisors of that number. Then it adds them
*   together based on the number of children
************************************************/
#include <stdio.h>
#include <stdlib.h>

// argc -> stores number of command-line arguments passed by the user including the name of the program
// argv[] -> is array of character pointers listing all the arguments
// ex -> ""./HW1 2 12"
// argc = 3
// argv[] = {./HW1, 2, 12}

void calcFactor(int factorNumber) {
    int factorList[50];
    printf("Factors of %d are: \n", factorNumber);
    for(int j =1; j <= factorNumber; j++)
    {
        int count = 0;
        if (factorNumber % j == 0) {
            factorList[count] = j;
            printf("%d\n", j);
        }
        count++;
    }
}


void createChildren(int numOfChildren) {
    // Need to create the number of children 1,2,4
    if (numOfChildren == 1) {

        printf("Number of Childern = %d\n", numOfChildren);

    } else if(numOfChildren == 2) {

        printf("Number of Childern = %d\n", numOfChildren);

    } else if (numOfChildren == 4) {

        printf("Number of Childern = %d\n", numOfChildren);

    }
}

int main(int argc, char *argv[]) {

    //variables
    int numOfChildren = strtol(argv[1], NULL, 10);
    int factorNumber = strtol(argv[2], NULL, 10);
    // int factorList[50] = calcFactor(factorNumber);

    createChildren(numOfChildren);
    calcFactor(factorNumber);
    return 0;

}
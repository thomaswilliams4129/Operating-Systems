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
// ex -> ""./HW1 2 12" 2
// argc = 3
// argv[] = {2,12}
int main(int argc, char *argv[]) {

    int numOfChildern = strtol(argv[1], NULL, 10);
    int number = strtol(argv[2], NULL, 10);
    int factorList[52];

    if (numOfChildern == 1) {
        printf("%d\n", numOfChildern);
    } else if(numOfChildern == 2) {
        printf("%d\n", numOfChildern);
    } else if (numOfChildern == 4) {
        printf("%d\n", numOfChildern);
    }

    printf("Factors of %d are: \n", number);
    for(int j =1; j <= number; j++)
    {
        int count = 0;
        if (number % j == 0) {
            factorList[count] = j;
            printf("%d\n", j);
        }
        count++;
    }

    // printf("argc = %d\n", argc);

    // for(int i = 1; i < argc; i++) {
    //     printf("argv postion %d = %s\n", i, argv[i]);
    // }
    return 0;

}
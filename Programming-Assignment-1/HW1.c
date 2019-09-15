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
#include <unistd.h>
#include <sys/wait.h>

// argc -> stores number of command-line arguments passed by the user including the name of the program
// argv[] -> is array of character pointers listing all the arguments
// ex -> ""./HW1 2 12"
// argc = 3
// argv[] = {./HW1, 2, 12}

void calcFactor(int factorNumber) {
    int factorList[50];
    printf("Factors of %d are: ", factorNumber);
    for(int j =1; j <= factorNumber; j++)
    {
        int count = 0;
        if (factorNumber % j == 0) {
            factorList[count] = j;
            printf("%d ", j);
        }
        count++;
    }
    printf("\n");
}


void createChildren(int numOfChildren) {
    if (numOfChildren == 1) {
        printf("Number of Childern = %d\n", numOfChildren);
        for(int i = 0; i < 1; i++) {
            if (fork()==0) {
                printf("[son] pid %d from [parent] pid %d\n", getpid(),getppid());
                exit(0);
            }
        } 
        for(int i = 0; i < 1; i++) {
            wait(NULL);
        }
    } else if(numOfChildren == 2) {
        printf("Number of Childern = %d\n", numOfChildren);
        for(int i = 0; i < 2; i++) {
            if (fork()==0) {
                printf("[son] pid %d from [parent] pid %d\n", getpid(),getppid());
                exit(0);
            }
        } 
        for(int i = 0; i < 2; i++) {
            wait(NULL);
        }
    } else if (numOfChildren == 3) {
        printf("Number of Childern = %d\n", numOfChildren);
        for(int i = 0; i < 3; i++) {
            if (fork()==0) {
                printf("[son] pid %d from [parent] pid %d\n", getpid(),getppid());
                exit(0);
            }
        } 
        for(int i = 0; i < 3; i++) {
            wait(NULL);
        }
    } else {
        printf("!!!!ERROR!!!! Input 1 to 3 children.\n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {

    //variables
    int numOfChildren = strtol(argv[1], NULL, 10);
    int factorNumber = strtol(argv[2], NULL, 10);
   
    // int factorList[50] = calcFactor(factorNumber);
    calcFactor(factorNumber);
    createChildren(numOfChildren);

    return 0;

}
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
// ex -> "./HW1 2 12"
// argc = 3
// argv[] = {./HW1, 2, 12}

int main(int argc, char *argv[]) {

    //variables
    int numOfChildren = strtol(argv[1], NULL, 10);
    int factorNumber = strtol(argv[2], NULL, 10);
    int factorList[101];

    int count = 0; // count for array length

    int fd[2];
    pipe(fd);

    //variable to store calling function's process id
	pid_t process_id;
    //variable to store parent function's process id
	pid_t p_process_id;



    int sum = 0;
    
     //factors the number entered in by the user
    // printf("Factors of %d are: ", factorNumber);
    for(int j =1; j <= factorNumber; j++)
    {
        if (factorNumber % j == 0) {
            factorList[count++] = j;
            // printf("%d ", j);
        }
    }
    printf("\n");

    // user inputs one child
    if (numOfChildren == 1) {

        //getppid() - will return process id of parent function
	    p_process_id = getppid();

        printf("I am the parent with pid: %d sending the array: ", p_process_id);
        for (int j = 0; j < count; j++) {
            printf("%d ", factorList[j]);   // print array
        }
        printf("\n");   // spacing

        int rc = fork();

        if (rc < 0) {
            // fork failed; exit
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            close(fd[0]);

            //getpid() - will return process id of calling function
	        process_id = getpid();

            for (int i=0; i<count; i++) {
                sum = sum + factorList[i];
            }
            write(fd[1], &sum, sizeof(sum));    // writes the sum
            write(fd[1], &process_id, sizeof(process_id));  // writes the child pid #
            printf("I am the child with pid: %d, adding the array ", process_id);
            for (int j = 0; j < count; j++) {
                printf("%d ", factorList[j]);   // print array
            }
            printf("and sending partial sum %d\n", sum);
            //sleep(1);
            close(0);
            exit(0);   //* kill the process after is done
        } else {
            // variable to store the final sum
            int final = 0;
            //variable to store parent function's process id
	        pid_t c_process_id;

            close(fd[1]);   // closes the write
            read(fd[0], &final, sizeof(sum));   // reads the write
            read(fd[0], &c_process_id, sizeof(c_process_id));   // reads the childs process id #
            printf("I am the parent with pid %d receiving from child with pid %d thepartial sum %d, the total sum is %d\n", p_process_id, c_process_id, final, final);
            close(fd[0]);   // closes the read
        }
    } else if (numOfChildren == 2) {
        
    }
    return 0;
}
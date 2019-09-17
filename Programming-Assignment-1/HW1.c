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
    int sum = 0;

    pid_t process_id;   //variable to store calling function's process id
	pid_t p_process_id; //variable to store parent function's process id

    // create pipes for communication
    int p1[2];  //pipe 1
    pipe(p1);
    int p2[2];  //pipe 2
    pipe(p2);
    int p3[2];
    pipe(p3);

    //factors the number entered in by the user
    // printf("Factors of %d are: ", factorNumber);
    for(int j =1; j <= factorNumber; j++)
    {
        if (factorNumber % j == 0) {
            factorList[count++] = j;
            // printf("%d ", j);
        }
    }

    // user inputs 1 child
    if (numOfChildren == 1) {
        //getppid() - will return process id of parent function
	    p_process_id = getppid();

        // ouput
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
            close(p1[0]);

            //getpid() - will return process id of calling function
	        process_id = getpid();

            for (int i=0; i<count; i++) {
                sum = sum + factorList[i];
            }

            write(p1[1], &sum, sizeof(sum));    // writes the sum
            write(p1[1], &process_id, sizeof(process_id));  // writes the child pid #

            // ouput
            printf("I am the child with pid: %d, adding the array ", process_id);
                for (int j = 0; j < count; j++) {
                    printf("%d ", factorList[j]);   // print array
                }
            printf("and sending partial sum %d\n", sum);
            close(p1[0]);
            //sleep(1);
            close(0);
            exit(0);   //* kill the process after is done
        } else {
            // variable to store the final sum
            int final = 0;
            //variable to store parent function's process id
	        pid_t c_process_id;

            close(p1[1]);   // closes the write
            read(p1[0], &final, sizeof(sum));   // reads the write
            read(p1[0], &c_process_id, sizeof(c_process_id));   // reads the childs process id #
            printf("I am the parent with pid %d receiving from child with pid %d thepartial sum %d, the total sum is %d\n", p_process_id, c_process_id, final, final);
            close(p1[0]);   // closes the read
        }
    } else if (numOfChildren == 2) {     // user inputs 2 child
        
        //getppid() - will return process id of parent function
	    p_process_id = getppid();

        printf("I am the parent with pid: %d sending the array: ", p_process_id);
        for (int j = 0; j < count; j++) {
            printf("%d ", factorList[j]);   // print array
        }
        printf("\n");   // spacing

        int rc1 = fork();
        int rc2 = fork();

        if (rc1 < 0) {
            // fork failed; exit
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc1 == 0) {  // first child
            close(p1[0]);

            //getpid() - will return process id of calling function
	        process_id = getpid();

            for (int i=0; i<count/2; i++) {
                sum = sum + factorList[i];  // add sum
            }

            write(p1[1], &sum, sizeof(sum));    // writes the sum
            write(p1[1], &process_id, sizeof(process_id));  // writes the child pid #
            printf("I am the child with pid: %d, adding the array ", process_id);
            for (int j = 0; j < count/2; j++) {
                printf("%d ", factorList[j]);   // print array
            }
            printf("and sending partial sum %d\n", sum);
            //sleep(1);
            close(0);
            exit(0);   //* kill the process after is done
        } else if (rc2 == 0) {  // second child
            close(p2[0]);

            //getpid() - will return process id of calling function
	        process_id = getpid();

            for (int i=count/2; i<count; i++) {
                sum = sum + factorList[i];  // add sum
            }

            write(p2[1], &sum, sizeof(sum));    // writes the sum
            write(p2[1], &process_id, sizeof(process_id));  // writes the child pid #
            printf("I am the child with pid: %d, adding the array ", process_id);
            for (int j = count/2; j < count; j++) {
                printf("%d ", factorList[j]);   // print array
            }
            printf("and sending partial sum %d\n", sum);
            close(p2[0]);
            //sleep(1);
            close(0);
            exit(0);   //* kill the process after is done

        }  else {
            // variable to store the final sum
            int final = 0;
            int sum1 = 0;
            int sum2 = 0;
            //variable to store child function's process id
	        pid_t c1_process_id;
            pid_t c2_process_id;

            close(p1[1]);   // closes the write
            read(p1[0], &sum1, sizeof(sum));   // reads the write
            read(p1[0], &c1_process_id, sizeof(c1_process_id));   // reads the childs process id #
            final = final + sum1;

            close(p2[1]);   // closes the write
            read(p2[0], &sum2, sizeof(sum));   // reads the write
            read(p2[0], &c2_process_id, sizeof(c2_process_id));   // reads the childs process id #
            final = final + sum2;

            wait(NULL);
            printf("I am the parent with pid %d receiving from child with pid %d the partial sum %d, and for child with pid %d the partial sum of %d, the total sum %d\n", p_process_id, c1_process_id, sum1, c2_process_id,sum2, final);
            close(p1[0]);   // closes the read
        }
    } else if (numOfChildren == 3) {
        // ! create the condition for creating 3 children
    }
    return 0;
}
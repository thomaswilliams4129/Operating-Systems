#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared_data[1000];

void *generate_fib_seq(void* number) {
    int i, firstNumber = 0, secondNumber = 1, nextNumber;
    
    /** This is to avoid ordered comparison between pointer and integer **/
    int *pointer;
    pointer = (int*) number;
    int total = *pointer;
    
    for (i = 0; i < total; i++) {
        shared_data[i] = firstNumber;
        nextNumber = firstNumber + secondNumber;
        firstNumber = secondNumber;
        secondNumber = nextNumber;
    }
    
    return 0;
}
void parent_output(int fibNumber) {
    printf("Output:\n");
    for(int i = 0; i < fibNumber; i++) {
        printf("%d ",shared_data[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    
    // user input from command line argument
    int fibNumber = atoi(argv[1]);
    
    // create thread
    pthread_t thread;
    
    //starts fibonacci thread
    pthread_create(&thread, NULL, generate_fib_seq, (void*) &fibNumber);
    
    //waits for thread to finish
    pthread_join(thread, NULL);
    
    //output to command prompt after thread finishes.
    parent_output(fibNumber);
    
    
    return 0;
}

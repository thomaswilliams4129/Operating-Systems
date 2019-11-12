#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared_data[1000];

void *generateFibSeq(void* number) {
    int i, firstNumber = 0, secondNumber = 1, nextNumber;
    
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


int main(int argc, char *argv[]) {
    
    int fibNumber = atoi(argv[1]);
    
    pthread_t thread; // create thread
    
    pthread_create(&thread, NULL, generateFibSeq, (void*) &fibNumber); //starts fibonacci thread
    pthread_join(thread, NULL); //waits for thread to finish
    
    
    //output to command prompt after thread finishes.
    printf("Output:\n");
    for(int i = 0; i < fibNumber; i++) {
        printf("%d ",shared_data[i]);
    }
    printf("\n");
    
    
    return 0;
}

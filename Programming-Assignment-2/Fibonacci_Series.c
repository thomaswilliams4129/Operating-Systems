#include <stdio.h>
#include <stdlib.h>


void generateFibSeq(int fibNumber) {
    int i, t1 = 0, t2 = 1, nextTerm;
    
    printf("Fibonacci Series: ");
    for (i = 1; i <= fibNumber; i++)
    {
        printf("%d ", t1);
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
    printf("\n\n");
}


int main(int argc, char *argv[]) {
    
    int fibNumber = atoi(argv[1]);
    generateFibSeq(fibNumber);
    
    
    
    return 0;
}

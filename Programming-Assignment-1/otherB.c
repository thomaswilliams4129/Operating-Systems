#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
int fd[2];
pipe(fd);

int fd2[2];
pipe(fd2);

int k;
int sum=0; 
int array1[6] = {2,3,7,-1,10,6};

printf("hello world, I am Parent the only one with process ID: (pid:%d)\n", (int) getpid());
    int rc = fork();
    int rc1 = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
       close(fd[0]);
       int i;
      for(i=0; i<3; i++){  //first correction here from 0-3
          sum = sum+array1[i];
       }
      write(fd[1], &sum, sizeof(sum));
     printf(" I am process %d and I am sending : %d to my parent\n", (int) getpid(),  sum);
     close(fd[1]);
     //sleep(1);
    close(0);
     exit(0);   //I am includeing exit(0) to kill the process after is done !!!!@
    }  else if (rc1==0){
         // printf("Hello, I am child 2, my pid is: (pid:%d)\n", (int) getpid());
          close(fd2[0]);
         // int sum =0;
           int k;
           for (k=3; k<6; k++){
           sum = sum+array1[k];
            }
          write(fd2[1], &sum, sizeof(sum));
          printf("I am process with id number %d  sending the  value:%d\n", (int) getpid(), sum);
          close(fd2[1]);
          //sleep(1);
          close(0);
          exit(0);
      } 

   else {
      int sum1, sum2;
      int final=0;
          
      close(fd[1]);
      read(fd[0], &sum1, sizeof(sum));
      final = final + sum1;
      close(fd2[1]);
      read(fd2[0], &sum2, sizeof(sum2));
      
    final = final +sum2;
    
    printf("I am the parent at the end with ID %d with a final sum of: %d \n" , (int) getpid(), final);
    close(fd[0]);
    close(fd2[0]);
    }
    return 0;
}

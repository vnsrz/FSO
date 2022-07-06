#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(void) {
  char *binaryPath = "/bin/ls";
  char *arg1 = "-a";
  char *arg2 = "/home/mine";
 
  execl(binaryPath, binaryPath, arg1, arg2, NULL);
 
  return 0;
}

int paiEFilho(){
    pid_t p, a;
    
    p=fork();
    a=fork();

    printf("sou #%d e meu pai é #%d\n", getpid(), getppid());
}

// p = 603
// p2 = 604
// a = 605
// a2 = 606

// p -> a -> p2 -> a2
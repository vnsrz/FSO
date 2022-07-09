#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int testaExec(void) {
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

pid_t c;

void seg(void){
	sleep(20);
	exit(0);
}

void sig_handler(int s){
	printf("sou %d e recebi %d\n", getpid(), s);
	kill(c, SIGUSR2);
}

int main(void){
    pid_t a, b, d, e, f, g;
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
    
	a = getpid();

	b = fork();
    if(b == 0) // estou no processo b
		seg();
	
	c=fork();
	if(c == 0){ // estou no processo c
		e = fork();
		if(e==0)	// estou no processo e
			seg();
		seg();
	}

	d = fork();
	if(d==0){ // estou no processo d
		f = fork();
		if(f == 0) // estou no processo f
			seg();
		g = fork();
		if(g == 0){ // estou no processo g
			sleep(10);
			kill(a, SIGUSR1);
			seg();
		} 
	}
		
	seg();
	
}

// p = 603
// p2 = 604
// a = 605
// a2 = 606

// p -> a -> p2 -> a2
// Funciona no meu console mas não no MOJ

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    char path[256];
    char arg[256];

    struct timeval antes;
    struct timeval depois;
    double atual, u_atual, total=0;

    int status, f_status;
    pid_t pid;

    while(scanf("%s %s", path, arg) != EOF){
        gettimeofday(&antes, NULL);
        pid = fork();

        if(pid == 0){
            execl(path, path, arg, NULL);
            perror("Erro");
            _exit(errno);

        }else{
            waitpid(pid, &status, 0);
            gettimeofday(&depois, NULL);

            atual = (double)depois.tv_sec - antes.tv_sec;
            u_atual = (double)depois.tv_usec - antes.tv_usec;
            atual = atual + u_atual/1000000;
            total += atual;

            if(WIFEXITED(status)) f_status = WEXITSTATUS(status);

            printf("> Demorou %.1lf segundos, retornou %d\n", atual, f_status);
        }
    }

    printf(">> O tempo total foi de %.1lf segundos\n", total);
    
    return 0;
}
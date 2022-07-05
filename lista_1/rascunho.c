#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void leMatriz(int** m, int n){
    int aux;
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            scanf("%d", &aux);
            m[i][j] = aux;
        }
    }
}

int** multiplicaMatrizes(int** a, int** b, int col, int resto) {
    int row = col/2;            //realizar so metade das linhas
    int rslt[row+resto][col];   //caso haja resto, realizar mais uma linha

    for (int i = 0; i < row+resto; i++) { // itera as linhas 
        for (int j = 0; j < col; j++) { // itera as colunas
            rslt[i][j] = 0;
 
            for (int k = 0; k < col; k++) { //
                rslt[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return rslt;
}

void criaFork(int** a, int** b, int n){
    pid_t filho1, filho2;
    int tamanho = n/2;
    int resto = n%2;
    
    int** resultado1 = criaMatriz(n);
    int** resultado2 = criaMatriz(n); 
    
    filho1 = fork(); // cria primeiro filho

    if(filho1 > 0){ // -------------------------------- pai
        filho2 = fork(); // cria segundo filho

        if(filho2 == 0){ // -------------------------------- filho 2
            resultado2 = multiplicaMatrizes(a, b, tamanho, resto);
        }else if (filho2 < 0){
            printf("Erro\n");
            
        }else{      // -------------------------------- pai 
            wait(NULL);
        }
    }else if (filho1 < 0){
        printf("Erro\n");   

    }else{              // -------------------------------- filho 1
        resultado1 = multiplicaMatrizes(a, b, tamanho, 0);
    } 
}

void printaMatriz(int** matriz, int n){
    printf("\n");
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            printf("%d ", matriz[i][j]);
        }
        // if(i == n-1)
        //     printf("\n");
        printf("\n");
    }
}

void limpaMatriz(int** matriz, int n){
    for (int i = 0; i < n; i++)
        free(matriz[i]);

    free(matriz);
}

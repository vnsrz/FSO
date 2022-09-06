#include <stdio.h>
#include <stdlib.h>

typedef struct Anomalia{
    int quadros;
    int pfs;
}anomalia;

anomalia belady;
int ocorre = 0;

typedef struct Fila{
    int *item;
    int capacidade;
    int frente, tras, tam;
}fila;

fila* initFila(int capacidade){
    fila *f = malloc(sizeof(fila));
    f->item = malloc(sizeof(int)*capacidade);
    f->capacidade = capacidade;
    f->frente = f->tam = 0;
    f->tras = capacidade - 1;

    return f;
}

int isFull(fila *f){
    return (f->tam == f->capacidade);
}

void remover(fila *f){
    //int item = f->item[f->frente];
    f->frente = (f->frente + 1) % f->capacidade;
    f->tam = f->tam - 1;
}

void inserir(fila *f, int item){
    if(isFull) remover(f);
    f->tras = (f->tras + 1) % f->capacidade;
    f->item[f->tras] = item;
    f->tam = f->tam + 1;
}

int busca(fila *f, int q, int x){
    for(int i=0; i<q; i++){
        if(f->item[i] == x) return 1;
    }
    return 0;
}

int testaSub(int q, int *p, int n){
    fila *f = initFila(q);
    int pf = 0;

    for(int i=0; i<n; i++){
        if(!busca(f, q, p[i])){
            pf++;
            inserir(f, p[i]);
        }
    }

    if(pf > belady.pfs && q > belady.quadros) ocorre = 1;

    printf("%d %d\n", q, pf);
    return pf;
}

int main(void){
    belady.quadros = 10000;
    belady.pfs = 10000;
    int n, q, pf;
    int *p;

    scanf("%d", &n);
    p = malloc(sizeof(int)*n); 

    for(int i=0; i<n; i++){
        scanf("%d", &p[i]);
    }

    scanf("%d", &q);
    belady.pfs = testaSub(q, p, n);
    belady.quadros = q;
    
    while(scanf("%d", &q) != EOF){
        testaSub(q, p, n);
    }

    if(ocorre) printf("Belady detectado\n");
    else printf("Sem anomalia\n");

    return 0;
}
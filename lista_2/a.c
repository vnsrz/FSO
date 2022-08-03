#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct Lista{
    long *elementos;
    int tam;
}lista;

typedef long Item;
#define less(A,B) ((A) < (B))
#define lesseq(A,B) ((A) <= (B))
#define exch(A,B) { Item t; t=A;A=B;B=t; }
#define cmpexch(A,B) { if (less(B,A)) exch(A,B); }

lista *lista_init(int n){
    lista *l = malloc(sizeof(lista));
    l->elementos = malloc(sizeof(long)*n);
    l->tam = n;

    return l;
}

int separa(Item *v, int l, int r){
    Item pivot = v[r];
    int j=l;

    for(int k=l; k<r; k++){
        if(lesseq(v[k],pivot)){
            exch(v[k], v[j]);
            j++;
        }
    }
    exch(v[j], v[r]);

    return j;
}

void quicksortm3(Item *v, int l, int r){
    if(lesseq(r,l)) return;
    
    int meio = (l+r)/2;
    cmpexch(v[meio],v[r]);
    cmpexch(v[l],v[meio]);
    cmpexch(v[r],v[meio]);

    int j = separa(v,l,r);
    quicksortm3(v,l,j-1);
    quicksortm3(v,j+1,r);
}

int compara(Item *v1, Item *v2, int n){
    for(int i=0; i<n; i++)
        if(v1[i]!=v2[i]) return 0;
    return 1;
}

void *linha1(void *arg){
    lista *v = (lista*)arg;
    quicksortm3(v->elementos,0,v->tam-1);
}

void printArray(lista *v)
{
    int i;

    printf("%ld", v->elementos[0]);
    for (i=1; i < v->tam; i++)
        printf(" %ld", v->elementos[i]);
    printf("\n");
}

int main(void){
    pthread_t tid;
    lista *v1, *v2;
    int n;

    scanf("%d", &n);
    
    v1 = lista_init(n);
    v2 = lista_init(n);

    for(int i=0; i<n; i++){
        scanf("%ld", &v1->elementos[i]);
    }

    for(int i=0; i<n; i++){
        scanf("%ld", &v2->elementos[i]);
    }

    pthread_create(&tid, NULL, linha1, v1); // ordena v1

    quicksortm3(v2->elementos,0,n-1); // ordena v2

    pthread_join(tid, NULL);

    compara(v1->elementos,v2->elementos,n)?printf("Mesmos elementos\n"):printf("Diferentes\n");

    return 0;
}
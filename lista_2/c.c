#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct args{
    unsigned l;
    unsigned r;
    unsigned *v;
}args;

int s;

void mergeArrays(unsigned *arr1, unsigned *arr2, int n1, int n2, unsigned *arr3){
    int i = 0, j = 0, k = 0;

    while (i<n1 && j <n2)
    {
        if (arr1[i] < arr2[j])
            arr3[k++] = arr1[i++];
        else
            arr3[k++] = arr2[j++];
    }

    while (i < n1)
        arr3[k++] = arr1[i++];
  
    while (j < n2)
        arr3[k++] = arr2[j++];
}

void *verificaSeed(void* arg){
    args *ptr = (args *)arg;
    unsigned seed = ptr->l, aux = ptr->l;
    int t, i=0;
    int *tam = (int *)malloc(sizeof(int));
    *tam = 0;

    while(aux <= ptr->r){
        for(int j=1;j<100000;j++) rand_r(&seed); 
        t = rand_r(&seed)%8;
        if(t == s){
            ptr->v[i++] = aux;
            (*tam)++;
        }
        seed = ++aux;
    }

    return tam;
}

int main(void){
    pthread_t tid;
    args arg1, arg2;
    unsigned mi, mf;
    unsigned *v;
    int *tam1, *tam2;
    
    scanf("%u %u %u",&mi, &mf, &s);

    arg1.v = malloc(sizeof(unsigned)*65536);
    arg2.v = malloc(sizeof(unsigned)*65536);
    v = malloc(sizeof(unsigned)*65536*2);

    if(mf != mi){
        int meio = (mf - mi)/2;
        arg1.l = mi;
        arg1.r = mi+meio;

        arg2.l = mi+meio+1;
        arg2.r = mf;

        pthread_create(&tid, NULL, verificaSeed, &arg1);
        tam2 = verificaSeed(&arg2);
        pthread_join(tid, (void *)&tam1);
        mergeArrays(arg1.v, arg2.v, *tam1, *tam2, v);
        for (int i=0; i < (*tam1)+(*tam2); i++) printf("%u\n", v[i]);

    }else{
        arg1.l = mi;
        arg1.r = mf;
        tam1 = verificaSeed(&arg1);
        for (int i=0; i < *tam1; i++) printf("%u\n", arg1.v[i]);
    }

    return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1, s2;

typedef struct Param{
    sem_t *smeu, *svizinho;
    int *x;
}param;

void *i10sv(void *arg){
    //int x = *(param*)arg->x;
    param *p = (param*)arg;
    sem_wait(p->smeu);
    int x = *(p->x);

    for(int i=0; i<10 ; i++){
        printf("=== %d\n", x++);
    }

    *(p->x) = x;
    sem_post(p->svizinho);

    return NULL;
}

int main(void){
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 1);

    int a = 3, b=11;
    param p1, p2;
    p1.x = &a;
    p1.smeu = &s2;
    p1.svizinho = &s1;

    p2.x = &b;
    p1.svizinho = &s2;
    p1.smeu = &s1;

    pthread_t t1, t2;

    pthread_create(&t1, NULL, i10sv, (void *)&p1);
    pthread_create(&t2, NULL, i10sv, (void *)&p2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("=== a: %d b: %d\n", a, b);

    return 0;
}
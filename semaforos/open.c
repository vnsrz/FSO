#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *fs;
    char buf[10];
    size_t sz; 

    fs = fopen("text.txt", "r");
    if(fs == NULL){
        perror("Erro");
        exit(1);
    }

    while (!feof(fs)){
        memset(buf, 0, strlen(buf));
        sz = fread((void *)buf, 9, 1, fs);
        buf[9] = '\0';
        printf("%s", buf);
    }
    printf("\n");
    
    fclose(fs);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define BUFFER 8192*sizeof(char)            // 8KiB

int comparaBytes(char *file1, char *file2){
    FILE *f1, *f2;
    long size1, size2;
    char tmp1, tmp2;   
    // char buf[BUFFER], buf2[BUFFER];

    f1 = fopen(file1, "r");
    f2 = fopen(file2, "r");

    if(f1 == NULL || f2 == NULL){
        perror("Erro");
        fclose(f1); fclose(f2);
        return 1;
    }

    // --------------------------- mede o tamanho dos arquivos
    fseek(f1, 0, SEEK_END);
    size1 = ftell(f1);
    rewind(f1);
    
    fseek(f2, 0, SEEK_END);
    size2 = ftell(f2);
    rewind(f2);
    
    if(size1 != size2){
        fclose(f1); fclose(f2);
        return 1;  
    } 
    
    // while (!feof(f1)){                              83p no moj, reduz muito o tempo de execução
    //     memset(buf, 0, strlen(buf));
    //     memset(buf2, 0, strlen(buf2));

    //     fread((void *)buf, BUFFER-1, 1, f1); 
    //     fread((void *)buf2, BUFFER-1, 1, f2);

    //     buf[BUFFER-1] = '\0';
    //     buf2[BUFFER-1] = '\0';

    //     if(strcmp(buf, buf2) != 0){
    //         fclose(f1); fclose(f2);
    //         return 1;
    //     }
    // }

    for(int i=0; i<size1; i++){
        fread(&tmp1, 1, 1, f1);
        fread(&tmp2, 1, 1, f2);

        if (tmp1 != tmp2) {
            fclose(f1); fclose(f2);
            return 1;
        }
    }
    
    fclose(f1); fclose(f2);
    return 0;
}

int main(int argc,char **argv){
    FILE *f1, *f2; 

    for (int i=1; i < argc; i++){ 
        for(int j=i+1; j < argc; j++){                           
            if(comparaBytes(argv[i], argv[j]))
                printf("%s %s diferentes\n", argv[i], argv[j]);
            else
                printf("%s %s iguais\n", argv[i], argv[j]);
        }                            
    }

    return 0;
}

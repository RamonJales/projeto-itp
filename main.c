#include <stdio.h>

int main() {
    FILE *file;

    file = fopen("/home/ramon/work-spaces/ws-c/projeto-final/databases/test2.txt", "a");

    if(file == NULL) {
        printf("Error!");
        return 1;
    }

    fprintf(file, "TESTANDO 123!");

    fclose(file);

    printf("Arquivo criado!");
    return 0;
}
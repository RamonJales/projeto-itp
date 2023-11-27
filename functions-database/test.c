#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int create_table(int colQty, char **colTyp, char **colNames, char pkName[], char tableName[]) {
    FILE *file;
    
    //create file
        //making path process
    //char target[1000] = "projeto-final/databases/";

        //needs to be implemented cut_off_empty_espaces
    
    char auxTableName[100];
    strcpy(auxTableName, tableName);
    strcat(auxTableName, ".txt");
    //strcat(target, auxTableName);

    //file = fopen(target, "w");
    file = fopen(auxTableName, "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    //create content file
        //header
    char header[256] = "nome: ";
    strcat(header, tableName);
    fprintf(file, header);
    fprintf(file, "\n");
    
        //primary key name
    fprintf(file, pkName);
    fprintf(file, "|");

    //columns
    for (int i = 0; i < colQty; i++)
    {
        fprintf(file, colNames[i]);
        fprintf(file, "-");
        fprintf(file, colTyp[i]);
        fprintf(file, "|");
    }
    fprintf(file,"\n");
    return 0;
}

int main() {
    int len = 2;

    char **v1 = (char**) malloc(len * sizeof(char *));
    v1[0] = strdup("s");
    v1[1] = strdup("s");

    char **v2 = (char**) malloc(len * sizeof(char *));
    v2[0] = strdup("name");
    v2[1] = strdup("password");

    char pk[] = "id";
    char tname[100] = "test1";

    create_table(len, v1, v2, pk, tname);

    for (int i = 0; i < len; i++) {
        free(v1[i]);
        free(v2[i]);
    }
    free(v1);
    free(v2);
    return 0;
}
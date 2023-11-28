#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//funções auxiliares
void cutOffEmptySpaces(char str[]) {
    int len = strlen(str);

    int i = 0;
    //encontra onde começa os caracteres da string
    while(i < len && isspace(str[i])) {
        i++;
    }

    //encontra o final da minha string
    int j = len;
    while(j > i && isspace(str[j-1])) {
        j--;
    }

    //move os caracteres para o inicio da sttring
    int k;
    for (k = 0; k < (j-i); k++) {
        str[k] = str[i+k];
    }

    //addicona caracter nulo
    str[k] = '\0';
    
}

int registerTable(char tableName[]) {
    FILE *file;

    file = fopen("databases.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    fprintf(file, tableName);
    fprintf(file, ";\n");

    fclose(file);
    return 0;
}

int create_table(int colQty, char **colTyp, char **colNames, char pkName[], char tableName[]) {
    FILE *file;
    
    //create file
        //making path process
    
    cutOffEmptySpaces(tableName);

    char auxTableName[100];
    strcpy(auxTableName, tableName);
    strcat(auxTableName, ".txt");

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
    fclose(file);

    int result = registerTable(tableName);
    return result;
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
    char tname[100] = "  test1  ";

    create_table(len, v1, v2, pk, tname);

    for (int i = 0; i < len; i++) {
        free(v1[i]);
        free(v2[i]);
    }
    free(v1);
    free(v2);
    return 0;
}
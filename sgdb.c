#include "sgdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//funções auxiliares
int openFileError(FILE *file) {
    if(file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    else {
        return 0;
    }
}

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

void extractStr(char *str, char *strDestiny, int position) {
    int j = 0;
    if(position < strlen(str)) {
        while(str[position] != '\0') {
            strDestiny[j] = str[position];
            position++;
            j++;
        }
    }
    strDestiny[j] = '\0';
}

int countChar(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        i++;
    }
}

void putStrSufix(char *str, char *sufix, char *destiny) {
    strcpy(destiny, str);
    strcat(destiny, sufix);
}

int registerTable(char tableName[]) {
    FILE *file;

    file = fopen("databases.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    fprintf(file, tableName);
    fprintf(file, "\n");

    fclose(file);
    return 0;
}

char* getInformationFromRow(char *tableName, char *flag) {
    FILE *file;
    char row[1000];

    //recuperar pk
    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);

    file = fopen(auxTableName, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return "N";
    }

    //encontrar linha desejada
    int len = strlen(flag);
    while(fgets(row, sizeof(row), file) != NULL) {
        int result = strncmp(flag, row, len);
        if(result == 0) {
            break;
        }
    }

    char *information = (char*) malloc(100*sizeof(char));
    extractStr(row, information, len+1);
    fclose(file);

    return information;
}

void updatePK(char *tableName, char *pk) {
    FILE *file;
    FILE *tmp;
    char row[1000];

    file = fopen(tableName, "r+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    tmp = fopen("tmp.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    while(fgets(row, sizeof(row), file) != NULL) {
        int result = strncmp("pk", row, 2);
        if(result == 0) {
            fprintf(tmp, "pk:");
            fprintf(tmp, pk);
            fprintf(tmp, "\n");
        }
        else {
            fprintf(tmp, row);
        }
    }

    remove(tableName);
    rename("tmp.txt", tableName);

    fclose(tmp);
    fclose(file);
}

//funções do banco
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
        //meta dados
    fprintf(file, "nome:");
    fprintf(file, tableName);
    fprintf(file, "\n");

    fprintf(file, "pk:");
    fprintf(file, "0\n");

    fprintf(file, "cols:");
    char col[100];
    sprintf(col, "%d", colQty);
    fprintf(file, col);
    fprintf(file, "\n");

    fprintf(file, pkName);
    fprintf(file, "|");

    //columns
    for (int i = 0; i < colQty; i++) {
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

int insert(char tableName[], char **colValues) {
    FILE *file;
    //recuperar pk
    char pk[100];
    strcpy(pk, getInformationFromRow(tableName, "pk"));
    int pkInt = atoi(pk) + 1;
    sprintf(pk, "%d", pkInt);

    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);
    file = fopen(auxTableName, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(file, pk);
    fprintf(file, "|");
    //adicionar os valores
        //pega o número de colunas
    char ncol[100];
    strcpy(ncol, getInformationFromRow(tableName, "cols"));
    int ncolInt = atoi(ncol);

    for (int i = 0; i < ncolInt; i++) {
        fprintf(file, colValues[i]);
        fprintf(file, "|");
    }
    fprintf(file, ";\n");

    fclose(file);

    updatePK(auxTableName, pk);

    return 0;
}
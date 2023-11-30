#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgdb.h"
#include "sgdbaux.h"
#include "straux.h"

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
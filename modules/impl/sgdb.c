#include "sgdb.h"
#include "sgdbaux.h"
#include "straux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//funções do banco
int create_table(int colQty, char **colNames, char pkName[], char tableName[]) {
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
    fprintf(file, "\n");

    fclose(file);

    updatePK(auxTableName, pk);

    return 0;
}

// void deleteTuple(char tableName[], char *primaryKey) {
//     FILE *file, *tmpFile;
//     char row[100];
//     int found = 0;

//     char auxTableName[100];
//     putStrSufix(tableName, ".txt", auxTableName);

//     file = fopen(auxTableName, "r");
//     if (file == NULL) {
//         printf("Erro ao abrir o arquivo da tabela \"%s\".\n", tableName);
//         return;
//     }

//     tmpFile = fopen("temp.txt", "w");
//     if (tmpFile == NULL) {
//         printf("Erro ao criar arquivo temporário.\n");
//         fclose(file);
//         return;
//     }

//     while (fgets(row, sizeof(row), file) != NULL) {
//         char *token = strtok(row, "|");
//         if (strcmp(token, primaryKey) == 0) {
//             found = 1;
//             continue; // corresponde a tupla a ser apagada
//         }
//         fprintf(tmpFile, "%s", row); 
//     }

//     fclose(file);
//     fclose(tmpFile);

//     if (!found) {
//         printf("Chave primária \"%s\" não encontrada na tabela \"%s\".\n", primaryKey, tableName);
//         remove("temp.txt"); 
//         return;
//     }

//     remove(auxTableName); 
//     rename("temp.txt", auxTableName); 

//     printf("Tupla com a chave primária \"%s\" removida com sucesso da tabela \"%s\".\n", primaryKey, tableName);
// }



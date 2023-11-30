#include "sgdb.h"
#include "sgdbaux.h"
#include "straux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//funções do banco
int create_table(int colQty, char **colNames, char *pkName, char *tableName) {
    FILE *file;
    
    //create file
    
    /*o processo de colocar o sufixo .txt está nessa função pelo fato de precisarmos do nome original.
    De qualquer modo iríamos ter que retirar esse fufixo.*/
    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);

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

void listTables() {
    FILE *file;
    char tableName[100];

    file = fopen("databases.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de tabelas.\n");
        return;
    }

    printf("Tabelas existentes:\n");
    while (fgets(tableName, sizeof(tableName), file) != NULL) {
        // Remove o caractere de nova linha se estiver
        size_t length = strlen(tableName);
        if (tableName[length - 1] == '\n') {
            tableName[length - 1] = '\0';
        }
        printf("- %s\n", tableName);
    }

    fclose(file);
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

void printDataFromTable(const char *tableName) {
    FILE *file;
    char filename[100];
    char line[100];

    strcpy(filename, tableName);
    strcat(filename, ".itp");

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error ao abrir a tabela ou o arquivo nao existe!\n");
        return;
    }

    printf("Dados da tabela'%s':\n", tableName);

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

 void deleteTuple(char tableName[], char *primaryKey) {
    FILE *file, *tmpFile;
    char row[100];
    int found = 0;

    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);

    file = fopen(auxTableName, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo da tabela \"%s\".\n", tableName);
        return;
    }

    tmpFile = fopen("temp.txt", "w");
    if (tmpFile == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }

    int len = strlen(primaryKey);
    while(fgets(row, sizeof(row), file) != NULL) {
        int result = strncmp(primaryKey, row, len);
        if (result != 0) {
            fputs(row, tmpFile);
        } else {
            found = 1; 
        }
    }

    fclose(file);
    fclose(tmpFile);

    if (!found) {
        printf("Chave primária \"%s\" não encontrada na tabela \"%s\".\n", primaryKey, tableName);
        remove("temp.txt"); 
        return;
    }

    remove(auxTableName); 
    rename("temp.txt", auxTableName); 

    printf("Tupla com a chave primária \"%s\" removida com sucesso da tabela \"%s\".\n", primaryKey, tableName);
}

void deleteTable(const char *tableName) {
    // Create file path
    char filePath[100];
    strcpy(filePath, tableName);
    strcat(filePath, ".txt");

    if (remove(filePath) == 0) {
        printf("Tabela \"%s\" removida com sucesso.\n", tableName);
    } else {
        printf("Erro ao remover a tabela \"%s\".\n", tableName);
    }
}

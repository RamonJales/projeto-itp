#include "interface.h"
#include "straux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLUMN_NAME 50

void interface() {
    printf("°---------------------------------------------------°\n");
    printf("Escolha a opção: \n");
    printf("1 - Criar tabela\n");
    printf("2 - Listar as tabelas existentes\n");
    printf("3 - Criar nova linha na tabela\n");
    printf("4 - Listar os dados de uma tabela existente\n");
    printf("5 - Achar um valor em uma tabela existente\n");
    printf("6 - Apagar uma linha de uma tabela\n");
    printf("7 - Apagar uma tabela\n");
    printf("°---------------------------------------------------°\n");
}

void interfaceCreateTable(int *colQty, char **colNames, char *pkName, char *tableName) {
    int result;

    // input do nome da tabela
    printf("Informe o nome da tabela: ");
    scanf("%s", tableName);
    cutOffEmptySpaces(tableName);

    // input da quantidade de colunas
    printf("Informe a quantidade de colunas: ");
    result = scanf("%d", colQty);

    colNames = (char**) realloc(colNames, (*colQty) * sizeof(char *));

    //input do nome da coluna pk
    printf("Informe o nome da chave primária: ");
    scanf("%s", pkName);
    cutOffEmptySpaces(pkName);
    removeNumberFromStrInit(pkName);
    removeCharFromString(tableName, '|');

    //input das colunas
    for (int i = 0; i < *colQty; i++) {
        printf("Informe o nome da coluna %d: ", i+1);

        char tmpName[MAX_COLUMN_NAME];
        scanf("%s", tmpName);
        colNames[i] = strdup(tmpName);
        
        cutOffEmptySpaces(colNames[i]);
        removeCharFromString(colNames[i], '|');
    }
}

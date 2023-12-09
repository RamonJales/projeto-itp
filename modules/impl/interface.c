#include "interface.h"
#include "straux.h"
#include "sgdbaux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    printf("8 - Sair\n");
    printf("°---------------------------------------------------°\n");
}

void interfaceCreateTable(int *colQty, char *colTyp, char **colNames, char *pkName, char *tableName) {
    int result;

    // input do nome da tabela
    printf("Informe o nome da tabela: ");
    scanf("%s", tableName);
    cutOffEmptySpaces(tableName);

    // input da quantidade de colunas
    printf("Informe a quantidade de colunas: ");
    result = scanf("%d", colQty);

    colNames = (char**) realloc(colNames, (*colQty) * sizeof(char *));
    colTyp = (char*) realloc(colTyp, (*colQty) * sizeof(char));

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

        printf("Informe o tipo da coluna %d: ", i+1);
        scanf(" %c", &colTyp[i]);
        getchar();
    }
}

void interfaceInsertTable(char *tableName, char **colValues, int *colQty) {
    printf("Informe o nome da tabela: ");
    scanf("%s", tableName);
    getchar();
    cutOffEmptySpaces(tableName);

    //pegar o valor da 
    char col[100];
    strcpy(col, getInformationFromRow(tableName, "cols"));
    *colQty = atoi(col);

    colValues = (char**) realloc(colValues, (*colQty) * sizeof(char *));

    for (int i = 0; i < (*colQty); i++) {
        printf("Informe o valor da coluna %d: ", i+1);

        char tmpName[MAX_COLUMN_NAME];
        fgets(tmpName, sizeof(tmpName), stdin);
        colValues[i] = strdup(tmpName);
        cutOffEmptySpaces(colValues[i]);
        removeCharFromString(colValues[i], '|');
    }
}

void interfacePrintDataFromTable(char *tableName) {
    printf("Informe o nome da tabela: ");
    fgets(tableName, sizeof(tableName), stdin);
    tableName[strcspn(tableName, "\n")] = '\0'; // Remover o caractere de nova linha, se presente
    
    for (int i = 0; tableName[i]; i++) {
        tableName[i] = tolower(tableName[i]);
    }
}

void interfaceSearchDataFromTable(char *tableName) {
    printf("Informe o nome da tabela: ");
    fgets(tableName, sizeof(tableName), stdin);
    tableName[strcspn(tableName, "\n")] = '\0';
}

void interfaceDeleteLine(char *tableName, char *pkName) {
    printf("Informe o nome da tabela: ");
    fgets(tableName, sizeof(tableName), stdin);
    tableName[strcspn(tableName, "\n")] = '\0';

    printf("Informe a chave primária da tupla a ser apagada: ");
    fgets(pkName, sizeof(pkName), stdin);
    pkName[strcspn(pkName, "\n")] = '\0';

    for (int i = 0; tableName[i]; i++) {
    tableName[i] = tolower(tableName[i]);
    }
}

void interfaceDeleteTable(char *tableName) {
    printf("Informe o nome da tabela a ser apagada: ");
    fgets(tableName, sizeof(tableName), stdin);
    tableName[strcspn(tableName, "\n")] = '\0';

    for (int i = 0; tableName[i]; i++) {
    tableName[i] = tolower(tableName[i]);
    }
}

void clearTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

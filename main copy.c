#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sgdb.h"
#include "interface.h"

#define MAX_PK_NAME 50
#define MAX_TABLE_NAME 50

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

int main() {
    int op;
    
    interface();

    printf("Informe a opção escolhida: ");
    scanf("%d", &op);

    switch (op) {
        case (1): //CRIAR TABELA
            int colQty;
            char **colNames;
            char pkName[MAX_PK_NAME];
            char tableName[MAX_TABLE_NAME];

            interfaceCreateTable(&colQty, colNames, pkName, tableName);      
            
            create_table(colQty, colNames, pkName, tableName);
            
            free(colNames);

            break;
        case (2): //LISTAR TABELAS
            listTables();
            break;
        case (3): 
            break;
        case (4)://PRINTAR OS DADOS DE UMA TABELA
            // printf("Informe o nome da tabela: ");
            // scanf("%s", &tableName);
            // for (int i = 0; tableName[i]; i++) {
            //     tableName[i] = tolower(tableName[i]);
            // }
            // printDataFromTable(tableName);
            // break;
        case (5):
            break;
        case (6): // APAGAR UMA TUPLA
            // printf("Informe o nome da tabela: ");
            // scanf("%s", tableName);
            // printf("Informe a chave primária da tupla a ser apagada: ");
            // scanf("%s", primaryKey);
            // for (int i = 0; tableName[i]; i++) {
            //     tableName[i] = tolower(tableName[i]);
            // }
            // deleteTuple(tableName, &primaryKey);
            // break;
        case (7): // APAGAR UMA TABELA
            // printf("Informe o nome da tabela a ser apagada: ");
            // scanf("%s", tableName);
            // for (int i = 0; tableName[i]; i++) {
            //     tableName[i] = tolower(tableName[i]);
            // }
            // deleteTable(tableName);
            // break;
    }
    return 0;
}
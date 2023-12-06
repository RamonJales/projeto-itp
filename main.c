#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sgdb.h"
#include "interface.h"

#define MAX_PK_NAME 50
#define MAX_TABLE_NAME 50

int main() {
    int op;

    interface();

    printf("Informe a opção escolhida: ");
    scanf("%d", &op);

    switch (op) {
        case (1): //CRIAR TABELA
            int colQty;
            char **colNames = (char**) malloc(sizeof(char *));
            char *colTyp = (char*) malloc(sizeof(char));
            char pkName[MAX_PK_NAME];
            char tableName[MAX_TABLE_NAME];

            interfaceCreateTable(&colQty, colTyp, colNames, pkName, tableName);      

            create_table(colQty, colTyp, colNames, pkName, tableName);

            for (int i = 0; i < colQty; i++) {
                free(colNames[i]);
                free(colTyp[i]);
            }
            
            free(colNames);
            free(colTyp);

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
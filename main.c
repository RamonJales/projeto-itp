#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sgdb.h"
#include "interface.h"
#include "straux.h"
#include "funcaux.h"
#include "constant.h"

int main() {
    int op;

    while (1) {
        clearTerminal();
        printf("Bem-vindo ao nosso SGDB!\n");
        interface();
       
        printf("Informe a opção escolhida: ");
        scanf("%d", &op);
        cleanBuffer();

        switch (op) {
            case 1: { //CRIAR TABELA
                int colQty;
                char **colNames = (char**) malloc(sizeof(char *));
                char *colTyp = (char*) malloc(sizeof(char));
                char pkName[MAX_PK_NAME];
                char tableName[MAX_TABLE_NAME];

                interfaceCreateTable(&colQty, colTyp, colNames, pkName, tableName);

                createTable(colQty, colTyp, colNames, pkName, tableName);

                freeMatrix(colQty, colNames);
                free(colTyp);
    
                printf("Tabela criada!\n");
                break;
            }
            case 2: //LISTAR TABELAS
                listTables();
                break;
            case 3: { //CRIAR NOVA LINHA
                int rowQty;
                printf("Quantas linha deseja adicionar? ");
                scanf("%d", &rowQty);
                
                for (int i = 0; i < rowQty; i++) {
                    int colQty;
                    char tableName[MAX_TABLE_NAME];
                    char **colValues = (char**) malloc(sizeof(char *));

                    interfaceInsertTable(tableName, colValues, &colQty);
                    insertLine(tableName, colValues);
                    freeMatrix(colQty, colValues);
                    printf("\n");
                }
                break;
            }
            case 4: {// PRINTAR OS DADOS DE UMA TABELA
                char tableName[MAX_TABLE_NAME];
                interfacePrintDataFromTable(tableName);
                printDataFromTable(tableName);
                getchar();
                break;
            }
            case 5: { //ACHAR UM VALOR NA TABELA
                char tableName[MAX_TABLE_NAME];
                interfaceSearchDataFromTable(tableName);
                searchDataFromTable(tableName);
                getchar();
                break;
            }
            case 6: {// APAGAR UMA LINE
                char pkName[MAX_PK_NAME];
                char tableName[MAX_TABLE_NAME];
                interfaceDeleteLine(tableName, pkName);
                deleteLine(tableName, pkName);
                break;
            }
            case 7: { // APAGAR UMA TABELA
                char tableName[MAX_TABLE_NAME];
                interfaceDeleteTable(tableName);
                deleteTable(tableName);
                break;
            }
            case 8: // Opção para sair do loop
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Escolha novamente.\n");
        }
        if (op == 8) {
            break; // Sai do loop principal se a opção for 8
        }
        printf("Pressione Enter para continuar...");
        getchar();
    }
    return 0;
}
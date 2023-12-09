#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sgdb.h"
#include "interface.h"

#define MAX_PK_NAME 50
#define MAX_TABLE_NAME 50
#define MAX_COLS 50
#define MAX_COL_VALUE_LENGTH 50

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

                create_table(colQty, colTyp, colNames, pkName, tableName);

                for (int i = 0; i < colQty; i++) {
                    free(colNames[i]);
                }
                
                free(colNames);
                free(colTyp);
    
                printf("Tabela criada!\n");
                break;
            }
            case 2: //LISTAR TABELAS
                listTables();
                break;
            case 3: { //CRIAR NOVA LINHA
                char tableName[MAX_TABLE_NAME];
                printf("Informe o nome da tabela: ");
                fgets(tableName, sizeof(tableName), stdin);
                tableName[strcspn(tableName, "\n")] = '\0';

                //Pegar a col values

                break;
            }
            case 4: {// PRINTAR OS DADOS DE UMA TABELA
                char tableName[MAX_TABLE_NAME];
                printf("Informe o nome da tabela: ");
                fgets(tableName, sizeof(tableName), stdin);
                tableName[strcspn(tableName, "\n")] = '\0'; // Remover o caractere de nova linha, se presente

                for (int i = 0; tableName[i]; i++) {
                    tableName[i] = tolower(tableName[i]);
                }

                printDataFromTable(tableName);
                break;
            }
            case 5: { //ACHAR UM VALOR NA TABELA
                char tableName[MAX_TABLE_NAME];

                printf("Informe o nome da tabela: ");
                fgets(tableName, sizeof(tableName), stdin);
                tableName[strcspn(tableName, "\n")] = '\0';

                searchDataFromTable(tableName);
                break;
            }
            case 6: {// APAGAR UMA TUPLA
                char pkName[MAX_PK_NAME];
                char tableName[MAX_TABLE_NAME];

                printf("Informe o nome da tabela: ");
                fgets(tableName, sizeof(tableName), stdin);
                tableName[strcspn(tableName, "\n")] = '\0';

                printf("Informe a chave primária da tupla a ser apagada: ");
                fgets(pkName, sizeof(pkName), stdin);
                pkName[strcspn(pkName, "\n")] = '\0';

                for (int i = 0; tableName[i]; i++) {
                    tableName[i] = tolower(tableName[i]);
                }

                deleteTuple(tableName, pkName);
                break;
            }
            case 7: { // APAGAR UMA TABELA
                char tableName[MAX_TABLE_NAME];
                printf("Informe o nome da tabela a ser apagada: ");
                fgets(tableName, sizeof(tableName), stdin);
                tableName[strcspn(tableName, "\n")] = '\0';

                for (int i = 0; tableName[i]; i++) {
                    tableName[i] = tolower(tableName[i]);
                }
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
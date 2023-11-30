#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *file;

    char tableName[100] = "test2";
    char line[100];
    char auxtableName[100];
    char primaryKey;
    int op;
    
    interface();

    printf("Informe a opção escolhida: ");
    scanf("%d", &op);

    switch (op)
    {
    case (1): //CRIAR TABELA
      /*printf("Informe a quantidade de colunas: ");
      printf("Informe o tipo(?) da coluna: ");
      printf("Informe o nome da tabela: ");
      printf("Informe o nome da tabela: ");
      printf("Informe o nome da tabela: ");
        
      create_table(int colQty, char **colTyp, char **colNames, char pkName[], char tableName[])
        create_table(len, v1, v2, pk, tname);*/
        printf("Tabela");
        break;
    case (2): //LISTAR TABELAS
        listTables();
        break;
    case (3): 
        break;
    case (4)://PRINTAR OS DADOS DE UMA TABELA
        printf("Informe o nome da tabela: ");
        scanf("%s", &tableName);
        for (int i = 0; tableName[i]; i++) {
            tableName[i] = tolower(tableName[i]);
        }
        printDataFromTable(tableName);
        break;
    case (5):
        break;
    case (6): // APAGAR UMA TUPLA
        printf("Informe o nome da tabela: ");
        scanf("%s", tableName);
        printf("Informe a chave primária da tupla a ser apagada: ");
        scanf("%s", primaryKey);
        for (int i = 0; tableName[i]; i++) {
            tableName[i] = tolower(tableName[i]);
        }
        deleteTuple(tableName, &primaryKey);
        break;
    case (7): // APAGAR UMA TABELA
        printf("Informe o nome da tabela a ser apagada: ");
        scanf("%s", tableName);
        for (int i = 0; tableName[i]; i++) {
            tableName[i] = tolower(tableName[i]);
        }
        deleteTable(tableName);
        break;
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum DataType {
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    STRING,
};

typedef struct Table {
    int tableId;
    char tableName[100];
} Table;

typedef struct {
    int numTables;
    Table *tables[100];
} Database;

void listTable(Database myDatabase){
    printf("Tabelas existentes:\n");
    for(int i = 0; i < myDatabase.numTables; i++) {
        printf("%s\n", myDatabase.tables[i]->tableName);
    }
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
        //não sei, alguma coisa vai disponibilizar
        printf("%s", line);
    }

    fclose(file);
}

void deleteTable(Database *myDatabase, const char *tableName) {
    int found = 0;
    for (int i = 0; i < myDatabase->numTables; i++) {
        if (strcmp(myDatabase->tables[i]->tableName, tableName) == 0) {
            free(myDatabase->tables[i]);
            for (int j = i; j < myDatabase->numTables - 1; j++) {
                myDatabase->tables[j] = myDatabase->tables[j + 1];
            }
            myDatabase->numTables--;
            found = 1;
            printf("Tabela '%s' apagada com sucesso!\n", tableName);
            break;
        }
    }
    if (!found) {
        printf("Tabela '%s' nao encontrada!\n", tableName);
    }
}

int main() {
    FILE *file;
    Database myDatabase;
    myDatabase.numTables = 0;
    char tableName[100] = "test2";
    char line[100];
    char auxTableName[100];
    int op;
    
    interface();

    printf("Informe a opção escolhida: ");
    scanf("%d", &op);

    switch (op)
    {
    case (1): //CRIAR TABELA
        printf("Tabela");
        break;
    case (2): //LISTAR TABELAS
        listTable(myDatabase);
        for (int i = 0; i < myDatabase.numTables; i++) {
            free(myDatabase.tables[i]);
        } 
        printf("Listagem completa!\n");
        break;
    case (3): 
        break;
    case (4)://PRINTAR OS DADOS DE UMA TABELA
        printf("Informe o nome da tabela: ");
        scanf("%s", auxTableName);
        for (int i = 0; auxTableName[i]; i++) {
            auxTableName[i] = tolower(auxTableName[i]);
        }
        printDataFromTable(tableName);
        break;
    case (5):
        break;
    case (6): 
        break;
    case (7)://APAGAR UMA TABELA
        printf("Informe o nome da tabela a ser apagada: ");
        scanf("%s", auxTableName);
        for (int i = 0; auxTableName[i]; i++) {
            auxTableName[i] = tolower(auxTableName[i]);
        }
        deleteTable(&myDatabase, auxTableName);
        break;
    }

    return 0;
}
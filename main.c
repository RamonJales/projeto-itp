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

typedef struct Table
{
    int tableId;
    char tableName[100];
} Table;

typedef struct 
{
    int numTables;
    Table *tables[100];
} Database;

void ListTable(Database myDatabase){
    printf("Tabelas existentes:\n");
    for(int i = 0; i < myDatabase.numTables; i++) {
        printf("%s\n", myDatabase.tables[i]->tableName);
    }
}


void pullDataFromTable(const char *tableName) {
    FILE *file;
    char filename[100];
    char line[100];

    strcpy(filename, tableName);
    strcat(filename, ".txt");

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

int main() {
    FILE *file;
    Database myDatabase;
    myDatabase.numTables = 0;
    char tableName[100] = "test1";
    char line[100];
    char auxTableName[100];

    /*ListTable(myDatabase); // função pra ver as tabelas existentes
    
    for (int i = 0; i < myDatabase.numTables; i++) {
        free(myDatabase.tables[i]);
    }

    printf("Listagem completa!\n");

    printf("Informe o nome da tabela: ");
    scanf("%s", tableName);*/

    for (int i = 0; tableName[i]; i++) {
        tableName[i] = tolower(tableName[i]);
    }
    
    pullDataFromTable(tableName);

    return 0;
}
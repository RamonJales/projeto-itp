#include "sgdbaux.h"
#include "straux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int registerTable(char tableName[]) {
    FILE *file;

    file = fopen("databases.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    fprintf(file, tableName);
    fprintf(file, "\n");

    fclose(file);
    return 0;
}

char* getInformationFromRow(char *tableName, char *flag) {
    FILE *file;
    char row[1000];

    //recuperar pk
    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);

    file = fopen(auxTableName, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    //encontrar linha desejada
    int len = strlen(flag);
    while(fgets(row, sizeof(row), file) != NULL) {
        int result = strncmp(flag, row, len);
        if(result == 0) {
            break;
        }
    }

    char *information = (char*) malloc(100*sizeof(char));
    extractStr(row, information, len+1);
    fclose(file);
    //free(information);

    return information;
}

void updatePK(char *tableName, char *pk) {
    FILE *file;
    FILE *tmp;
    char row[1000];

    file = fopen(tableName, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    tmp = fopen("tmp.txt", "w");
    if (tmp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    while(fgets(row, sizeof(row), file) != NULL) {
        int result = strncmp("pk:", row, 3);
        if(result == 0) {
            fprintf(tmp, "pk:");
            fprintf(tmp, pk);
            fprintf(tmp, "\n");
        }
        else {
            fprintf(tmp, row);
        }
    }

    remove(tableName);
    rename("tmp.txt", tableName);

    fclose(tmp);
    fclose(file);
}

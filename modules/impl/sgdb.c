#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgdb.h"
#include "sgdbaux.h"
#include "straux.h"
#include "constant.h"
#include "interface.h"

//Funções do banco
int createTable(int colQty, char *colTyp, char **colNames, char *pkName, char *tableName) {
    FILE *file;
    
    //Cria arquivo   
    /*O processo de colocar o sufixo .txt está nessa função pelo fato de precisarmos do nome original.
    De qualquer modo iríamos ter que retirar esse fufixo.*/
    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);
    file = fopen(auxTableName, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    //Cria metadados
    fprintf(file, "nome:");
    fprintf(file, tableName);
    fprintf(file, "\n");
    fprintf(file, "pk:0\n");

    //Deve ser int, pois usamos esse valor para alocação dinâmica na interface
    fprintf(file, "cols:");
    char col[100];
    sprintf(col, "%d", colQty);
    fprintf(file, col);
    fprintf(file, "\n");

    fprintf(file, pkName);
    fprintf(file, "|");

    //Colunas
    for (int i = 0; i < colQty; i++) {
        fprintf(file, colNames[i]);
        fprintf(file, "-");

        char strChar[2];
        strChar[0] = colTyp[i];
        strChar[1] = '\0';

        fprintf(file, strChar);
        fprintf(file, "|");
    }
    fprintf(file,"\n");
    fclose(file);

    int result = registerTable(tableName);
    return result;
}

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

int insertLine(char *tableName, char **colValues) {
    FILE *file;
    
    //Recuperar pk
    char pk[100];
    strcpy(pk, getInformationFromRow(tableName, "pk:"));

    int pkInt = atoi(pk) + 1;
    sprintf(pk, "%d", pkInt);

    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);

    file = fopen(auxTableName, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(file, pk);
    fprintf(file, "|");

    //Pega o número de colunas
    char ncol[100];
    strcpy(ncol, getInformationFromRow(tableName, "cols"));
    int ncolInt = atoi(ncol);

    //Adicionar os valores
    for (int i = 0; i < ncolInt; i++) {
        fprintf(file, colValues[i]);
        fprintf(file, "|");
    }
    fprintf(file, "\n");

    fclose(file);

    updatePK(auxTableName, pk);

    return 0;
}

void printDataFromTable(char *tableName) {
    FILE *file;
    char line[100];

    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);

    file = fopen(auxTableName, "r");

    if (file == NULL) {
        printf("Error ao abrir a tabela ou o arquivo nao existe!\n");
        return;
    }

    printf("Dados da tabela '%s':\n", tableName);

    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    printf("%s", line);

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, "|");
        while (token != NULL) {
            printf("%-10s", token); 
            token = strtok(NULL, "|");
        }
        printf("\n");
    }

    fclose(file);
}

void searchDataFromTable(char *tableName) {
    FILE *file;
    int colQty;
    int searchOption;
    char colNames[100][MAX_TABLE_NAME];
    char searchColName[MAX_STR_LENGHT];
    char searchValue[MAX_STR_LENGHT];
    char line[MAX_LINE_LENGHT];
    char colValues[100][100];
    char strColType[10];

    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);
    
    file = fopen(auxTableName, "r");

    if (file == NULL) {
        printf("Erro ao abrir a tabela \"%s\".\n", tableName);
        printf("\n");
        return;
    }

    //Pega o nome das colunas (exceto a da pk) e coloca no vetor
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    colQty = atoi(strchr(line, ':') + 1); 
    fgets(line, sizeof(line), file);

    for (int i = 0; i < colQty; i++) {
        char strTmp[100];
        char strAux[100];

        //Tira o pk
        strcpy(strTmp, strchr(line, '|') + 1);
        //Tira as colunas(de tras) desnecessarias
        for (int j = 0; j < i; j++) {
            strcpy(strTmp, strchr(strTmp, '|') + 1);
        }

        cutStrUntilFirstOccurrence(strAux, strTmp, '|');
        strcpy(colNames[i], strAux);
    }

    //Imprime o nome das colunas
    printf("Colunas disponíveis na tabela '%s':\n", tableName);
    for (int i = 0; i < colQty; i++) {
        //Imprime sem o tipo da coluna
        char *str = strchr(colNames[i], '-');
        int indexStr = str - colNames[i];
        printf("%d. %.*s\n", i+1, indexStr, colNames[i]);
    }
    printf("\n");

    //Selecionar a coluna
    printf("Selecione o número da coluna para pesquisar: ");
    //Colunas começam de 1 (a pk é a 0, mas ela não é printada)
    int selectedCol;
    scanf("%d", &selectedCol);
    printf("\n");

    //Tratamento de erro do input
    if (selectedCol < 1 || selectedCol > colQty) {
        printf("Seleção de coluna inválida.\n");
        fclose(file);
        printf("\n");
        return;
    }

    //Pegar o tipo da coluna
    strcpy(strColType, strchr(colNames[selectedCol-1], '-') + 1);
    char colType = strColType[0];

    //Pegar valores das colunas
        //Varre as linhas
    int j = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char auxLine[MAX_LINE_LENGHT];
        char tmpLine[MAX_LINE_LENGHT];
        //Na linha em que ele estiver, ele pega a informação apenas da coluna selecionadas 
            //Varre as colunas. O strcht pega a primeira ocorrencia do char, mas eu não quero a primeira ocorrencia
        for(int i = 0; i< selectedCol; i++) {
            if (i == 0) {
                strcpy(auxLine, strchr(line, '|') + 1);
            } else {
                strcpy(auxLine, strchr(auxLine, '|') + 1);
            }
        }

        //Tira o lixo da informação (colunas restantes)
        cutStrUntilFirstOccurrence(tmpLine, auxLine, '|');
        strcpy(colValues[j], tmpLine);
        j++;
    }

    char *str = strchr(colNames[selectedCol-1], '-');
    int indexStr = str - colNames[selectedCol-1];
    printf("Digite o valor para pesquisar na coluna '%.*s': ", indexStr, colNames[selectedCol-1]);
    scanf("%s", searchValue);
    printf("\n");

    interfaceMenuSearchData(searchValue);
    printf("\n");
    
    printf("Escolha a opção de pesquisa: ");
    scanf("%d", &searchOption);
    printf("\n");

    printf("Resultados da pesquisa:\n");

    if (searchOption == 1) {
        for (int i = 0; i < j; i++) {
            //Tipo int
            if(colType == 'i') {
                //Transformar o valor para inteiro
                int intColVal = atoi(colValues[i]);
                int intSearchVal = atoi(searchValue);
                //Verificação
                if(intColVal > intSearchVal) {
                    printf("valor: %d\n", intColVal);
                }
            }
            //Tipo float
            if(colType == 'f') {
                float fColVal = (float) atof(colValues[i]);
                float fSearchVal = (float) atof(searchValue);
                //Verificação
                if(fColVal > fSearchVal) {
                    printf("valor: %f\n", fColVal);
                }
            }
            //Tipo double 
            if(colType == 'd') {
                double colVal = atof(colValues[i]);
                double searchVal = atof(searchValue);
                //Verificação
                if(colVal > searchVal) {
                    printf("valor: %f\n", colVal);
                }
            }
            //Tipo char 
            if(colType == 'c') {
                char colVal = colValues[i][0];
                char searchVal = searchValue[0];
                //Verificação
                if(colVal > searchVal) {
                    printf("valor: %c\n", colVal);
                }
            }
            //Tipo string 
            if(colType == 's') {
                //Verificação
                int result = strcmp(colValues[i], searchValue);
                if(result > 0) {
                    printf("valor: %s\n", colValues[i]);
                }
            }
        }
    } else if (searchOption == 2) {
        for (int i = 0; i < j; i++) {
            if(colType == 'i') {
                int intColVal = atoi(colValues[i]);
                int intSearchVal = atoi(searchValue);
                if(intColVal >= intSearchVal) {
                    printf("valor: %d\n", intColVal);
                }
            }
            if(colType == 'f') {
                float fColVal = (float) atof(colValues[i]);
                float fSearchVal = (float) atof(searchValue);
                if(fColVal >= fSearchVal) {
                    printf("valor: %f\n", fColVal);
                }
            }
            if(colType == 'd') {
                float colVal = atof(colValues[i]);
                float searchVal = atof(searchValue);
                if(colVal >= searchVal) {
                    printf("valor: %f\n", colVal);
                }
            }
            if(colType == 'c') {
                char colVal = colValues[i][0];
                char searchVal = searchValue[0];
                if(colVal >= searchVal) {
                    printf("valor: %c\n", colVal);
                }
            }
            if(colType == 's') {
                int result = strcmp(colValues[i], searchValue);
                if(result >= 0) {
                    printf("valor: %s\n", colValues[i]);
                }
            }
        }
    } else if (searchOption == 3) {
        for (int i = 0; i < j; i++) {
            if(colType == 'i') {
                int intColVal = atoi(colValues[i]);
                int intSearchVal = atoi(searchValue);
                if(intColVal == intSearchVal) {
                    printf("valor: %d\n", intColVal);
                }
            }
            if(colType == 'f') {
                float fColVal = (float) atof(colValues[i]);
                float fSearchVal = (float) atof(searchValue);
                if(fColVal == fSearchVal) {
                    printf("valor: %f\n", fColVal);
                }
            }
            if(colType == 'd') {
                float colVal = atof(colValues[i]);
                float searchVal = atof(searchValue);
                if(colVal == searchVal) {
                    printf("valor: %f\n", colVal);
                }
            }
            if(colType == 'c') {
                char colVal = colValues[i][0];
                char searchVal = searchValue[0];
                if(colVal == searchVal) {
                    printf("valor: %c\n", colVal);
                }
            }
            if(colType == 's') {
                int result = strcmp(colValues[i], searchValue);
                if(result == 0) {
                    printf("valor: %s\n", colValues[i]);
                }
            }
        }
    } else if (searchOption == 4) {
        for (int i = 0; i < j; i++) {
            if(colType == 'i') {
                int intColVal = atoi(colValues[i]);
                int intSearchVal = atoi(searchValue);
                if(intColVal < intSearchVal) {
                    printf("valor: %d\n", intColVal);
                }
            }
            if(colType == 'f') {
                float fColVal = (float) atof(colValues[i]);
                float fSearchVal = (float) atof(searchValue);
                if(fColVal < fSearchVal) {
                    printf("valor: %f\n", fColVal);
                }
            }
            if(colType == 'd') {
                float colVal = atof(colValues[i]);
                float searchVal = atof(searchValue);
                if(colVal < searchVal) {
                    printf("valor: %f\n", colVal);
                }
            }
            if(colType == 'c') {
                char colVal = colValues[i][0];
                char searchVal = searchValue[0];
                if(colVal < searchVal) {
                    printf("valor: %c\n", colVal);
                }
            }
            if(colType == 's') {
                int result = strcmp(colValues[i], searchValue);
                if(result < 0) {
                    printf("valor: %s\n", colValues[i]);
                }
            }
        }
    } else if (searchOption == 5) {
        for (int i = 0; i < j; i++) {
            if(colType == 'i') {
                int intColVal = atoi(colValues[i]);
                int intSearchVal = atoi(searchValue);
                if(intColVal <= intSearchVal) {
                    printf("valor: %d\n", intColVal);
                }
            }
            if(colType == 'f') {
                float fColVal = (float) atof(colValues[i]);
                float fSearchVal = (float) atof(searchValue);
                if(fColVal <= fSearchVal) {
                    printf("valor: %f\n", fColVal);
                }
            }
            if(colType == 'd') {
                float colVal = atof(colValues[i]);
                float searchVal = atof(searchValue);
                if(colVal <= searchVal) {
                    printf("valor: %f\n", colVal);
                }
            }
            if(colType == 'c') {
                char colVal = colValues[i][0];
                char searchVal = searchValue[0];
                if(colVal <= searchVal) {
                    printf("valor: %c\n", colVal);
                }
            }
            if(colType == 's') {
                int result = strcmp(colValues[i], searchValue);
                if(result <= 0) {
                    printf("valor: %s\n", colValues[i]);
                }
            }
        }
    } else if (searchOption == 6) {
        if(colType == 's') {
            for (int i = 0; i < j; i++) {
                //Se a função encontrar o searchValue em colValues[i], ele retorna o ponteiro para a posição onde essa ocorrencia ocorre
                if(strstr(colValues[i], searchValue) != NULL) {
                    printf("valor: %s\n", colValues[i]);
                }
            }
        }
    }

    fclose(file);
}

void deleteLine(char *tableName, char *pkName) {
    FILE *file, *tmpFile;
    char row[100];
    int found = 0;

    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);

    file = fopen(auxTableName, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo da tabela \"%s\".\n", tableName);
        return;
    }

    tmpFile = fopen("temp.txt", "w");
    if (tmpFile == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }

    int len = strlen(pkName);
    while(fgets(row, sizeof(row), file) != NULL) {
        int result = strncmp(pkName, row, len);
        if (result != 0) {
            fputs(row, tmpFile);
        } else {
            found = 1; 
        }
    }

    fclose(file);
    fclose(tmpFile);

    if (!found) {
        printf("Chave primária \"%s\" não encontrada na tabela \"%s\".\n", pkName, tableName);
        remove("temp.txt"); 
        return;
    }

    remove(auxTableName); 
    rename("temp.txt", auxTableName); 

    printf("Tupla com a chave primária \"%s\" removida com sucesso da tabela \"%s\".\n", pkName, tableName);
}

void deleteTable(char *tableName) {
    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);

    if (remove(auxTableName) == 0) {
        printf("Tabela \"%s\" removida com sucesso.\n", tableName);
    } else {
        printf("Erro ao remover a tabela \"%s\".\n", tableName);
    }

    //Apagar nome da tabela no databases
    FILE *file;
    FILE *tmp;
    char row[MAX_LINE_LENGHT];
    file = fopen("databases.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    tmp = fopen("tmp.txt", "w");
    if (tmp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int len = strlen(tableName);
    while(fgets(row, sizeof(row), file) != NULL) {
        int result = strncmp(tableName, row, len);
        if(result != 0) {
            fprintf(tmp, row);
        }
    }
    remove("databases.txt");
    rename("tmp.txt", "databases.txt");

    fclose(tmp);
    fclose(file);
}

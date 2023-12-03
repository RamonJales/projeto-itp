#include "sgdb.h"
#include "sgdbaux.h"
#include "straux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//funções do banco
int create_table(int colQty, char *colTyp, char **colNames, char *pkName, char *tableName) {
    FILE *file;
    
    //create file    
    /*o processo de colocar o sufixo .txt está nessa função pelo fato de precisarmos do nome original.
    De qualquer modo iríamos ter que retirar esse fufixo.*/
    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);

    file = fopen(auxTableName, "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    //create content file
        //meta dados
    fprintf(file, "nome:");
    fprintf(file, tableName);
    fprintf(file, "\n");

    fprintf(file, "pk:");
    fprintf(file, "0\n");

    fprintf(file, "cols:");
    char col[100];
    sprintf(col, "%d", colQty);
    fprintf(file, col);
    fprintf(file, "\n");

    fprintf(file, pkName);
    fprintf(file, "|");

    //columns
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

int insert(char *tableName, char **colValues) {
    FILE *file;
    //recuperar pk
    char pk[100];
    strcpy(pk, getInformationFromRow(tableName, "pk"));
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
    //adicionar os valores
        //pega o número de colunas
    char ncol[100];
    strcpy(ncol, getInformationFromRow(tableName, "cols"));
    int ncolInt = atoi(ncol);

    for (int i = 0; i < ncolInt; i++) {
        fprintf(file, colValues[i]);
        fprintf(file, "|");
    }
    fprintf(file, "\n");

    fclose(file);

    updatePK(auxTableName, pk);

    return 0;
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

void searchDataFromTable(char *tableName) {
    FILE *file;
    char colNames[100][100]; // Matriz para armazenar nomes das colunas
    int colQty;
    char searchColName[100];
    char searchValue[100];
    int searchOption;
    char line[100];
    char colValues[100][100];
    char colType;

    char auxTableName[100];
    putStrSufix(tableName, ".txt", auxTableName);
    
    file = fopen(auxTableName, "r");

    if (file == NULL) {
        printf("Erro ao abrir a tabela \"%s\".\n", tableName);
        return;
    }

    //pega o nome das colunas(exceto a do pk) e coloca no vetor
    fgets(line, sizeof(line), file); // Ignorar a linha com "nome:tableName"
    fgets(line, sizeof(line), file); // Ignorar a linha com "pk:0"
    fgets(line, sizeof(line), file); // Ignorar a linha com "cols:colQty"
    colQty = atoi(strchr(line, ':') + 1); 

    for (int i = 0; i <= colQty; i++) {
        fscanf(file, "%[^|]|", colNames[i]); 
    }
    fscanf(file, "\n");

    //falta retirar o "-type" do nome da coluna e colocar o tipo em um outro vetor

    //imprime o nome das colunas
    printf("Colunas disponíveis na tabela '%s':\n", tableName);
    for (int i = 1; i <= colQty; i++) {
        printf("%d. %s\n", i, colNames[i]);
    }

    //selecionar a coluna
    printf("Selecione o número da coluna para pesquisar: ");
    //colunas começam de 1(a pk é a 0, mas ela não é printada)
    int selectedCol;
    scanf("%d", &selectedCol);

    //tratamento de erro do input
    if (selectedCol < 1 || selectedCol > colQty) {
        printf("Seleção de coluna inválida.\n");
        fclose(file);
        return;
    }

    //pegar valores das colunas
        //varre as linhas
    int j = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char auxLine[1000];
        //Na linha em que ele estiver, ele pega a informação apenas da coluna selecionadas 
            //varre as colunas
        for(int i = 0; i< selectedCol; i++) {
            strcpy(auxLine, strchr(line, '|') + 1);
        }

        //falta deletar os caracteres restantes da string
        //se vc escolheu a coluna 1:
        //name|password|
        //deletar: |password|

        strcpy(colValues[j], auxLine);
        j++;
    }

    printf("Digite o valor para pesquisar na coluna '%s': ", colNames[selectedCol]);
    scanf("%s", searchValue);

    printf("Opções de pesquisa:\n");
    printf("1. Valores maior que '%s'\n", searchValue);
    printf("2. Valores maior ou igual a '%s'\n", searchValue);
    printf("3. Valores igual a '%s'\n", searchValue);
    printf("4. Valores menor que '%s'\n", searchValue);
    printf("5. Valores menor ou igual a '%s'\n", searchValue);
    printf("6. Valores próximos a '%s' (apenas para colunas do tipo string)\n", searchValue);
    
    printf("Escolha a opção de pesquisa: ");
    scanf("%d", &searchOption);

    printf("Resultados da pesquisa na coluna '%s':\n", searchColName);

    // ATUALIZAR SWITCH
    switch (searchOption) {
    case(1) :
        for (int i = 0; i < j; i++) {
            //deve haver uma verificação para saber qual é o tipo da coluna
            //tipo int
            if(colType == 'i') {
                //transformar o valor para inteiro
                int intColVal = atoi(colValues[i]);
                int intSearchVal = atoi(searchValue);
                //verificação
                if(intColVal > intSearchVal) {
                    printf("%d\n", intColVal);
                }
            }
            //tipo float
            if(colType == 'f') {
                //transformar o valor para float

                //verificação
                if() {

                }
            }
            //tipo double 
            if(colType == 'd') {
                //transformar o valor para double

                //verificação
                if() {
                    
                }
            }
            //tipo char 
            if(colType == 'c') {
                //transformar o valor para char

                //verificação
                if() {
                    
                }
            }
            //tipo string 
            if(colType == 's') {
                //transformar o valor para string

                //verificação
                if() {
                    
                }
            }
        }
        break;
    case(2):
        for (int i = 0; i < j; i++) {
            //tipo int
            if() {

            }
            //tipo float
            if() {

            }
            //tipo double 
            if() {

            }
            //tipo char 
            if() {

            }
            //tipo string 
            if() {

            }
        }
        break;
    case(3) :
        break;
    case(4):
        break;
    case(5) :
        break;
    case(6):
        break;
    }

    fclose(file);
}

void deleteTuple(char *tableName, char *primaryKey) {
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

    int len = strlen(primaryKey);
    while(fgets(row, sizeof(row), file) != NULL) {
        int result = strncmp(primaryKey, row, len);
        if (result != 0) {
            fputs(row, tmpFile);
        } else {
            found = 1; 
        }
    }

    fclose(file);
    fclose(tmpFile);

    if (!found) {
        printf("Chave primária \"%s\" não encontrada na tabela \"%s\".\n", primaryKey, tableName);
        remove("temp.txt"); 
        return;
    }

    remove(auxTableName); 
    rename("temp.txt", auxTableName); 

    printf("Tupla com a chave primária \"%s\" removida com sucesso da tabela \"%s\".\n", primaryKey, tableName);
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

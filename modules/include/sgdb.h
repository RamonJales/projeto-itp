#ifndef SGDB_H
#define SGDB_H

int create_table(int colQty, char *colTyp, char **colNames, char *pkName, char *tableName);

void listTables();

int insert(char *tableName, char **colValues);

void printDataFromTable(char *tableName);

void searchDataFromTable(char *tableName); 

void deleteLine(char *tableName, char *pkName);

void deleteTable(char *tableName);

#endif
#ifndef SGDB_H
#define SGDB_H

int createTable(int colQty, char *colTyp, char **colNames, char *pkName, char *tableName);

void listTables();

int insertLine(char *tableName, char **colValues);

void printDataFromTable(char *tableName);

void searchDataFromTable(char *tableName); 

void deleteLine(char *tableName, char *pkName);

void deleteTable(char *tableName);

#endif
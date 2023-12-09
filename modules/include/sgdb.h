#ifndef SGDB_H
#define SGDB_H

int create_table(int colQty, char *colTyp, char **colNames, char *pkName, char *tableName);

void listTables();

int insert(char *tableName, char **colValues);

void printDataFromTable(const char *tableName);

void searchDataFromTable(char *tableName); 

void deleteTuple(char *tableName, char *pkName);

void deleteTable(const char *tableName);

#endif
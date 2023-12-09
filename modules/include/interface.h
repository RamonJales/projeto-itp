#ifndef INTERFACE_H
#define INTERFACE_H

void interface();

void interfaceCreateTable(int *colQty, char *colTyp, char **colNames, char *pkName, char *tableName);

void interfacePrintDataFromTable(char *tableName);

void interfaceSearchDataFromTable(char *tableName);

void interfaceDeleteLine(char *tableName, char *pkName);

void interfaceDeleteTable(char *tableName);

void clearTerminal();

#endif
#ifndef SGDB_H
#define SGDB_H

#include <stdio.h>

int openFileError(FILE *file);

void cutOffEmptySpaces(char str[]);

void extractStr(char *str, char *strDestiny, int position);

int countChar(char *str);

void putStrSufix(char *str, char *sufix, char *destiny);

int registerTable(char tableName[]);

char* getInformationFromRow(char *tableName, char *flag);

void updatePK(char *tableName, char *pk);

int create_table(int colQty, char **colTyp, char **colNames, char pkName[], char tableName[]);

int insert(char tableName[], char **colValues);

#endif
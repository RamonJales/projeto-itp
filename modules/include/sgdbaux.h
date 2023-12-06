#ifndef SGDBAUX_H
#define SGDBAUX_H

#include <stdio.h>

int openFileError(FILE *file);

int registerTable(char tableName[]);

char* getInformationFromRow(char *tableName, char *flag);

void updatePK(char *tableName, char *pk);

// void searchGreaterValues(char colType, char **colValues, char *searchValue);

// void searchGreaterOrEqValues(char colType, char **colValues, char *searchValue);

// void searchEqValues(char colType, char **colValues, char *searchValue);

// void searchSmallerValues(char colType, char **colValues, char *searchValue);

// void searchSmallerOrEqValues(char colType, char **colValues, char *searchValue);

// void searchCloseValues(char colType, char **colValues, char *searchValue);

#endif
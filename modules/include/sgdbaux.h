#ifndef SGDBAUX_H
#define SGDBAUX_H

#include <stdio.h>

int openFileError(FILE *file);

int registerTable(char tableName[]);

char* getInformationFromRow(char *tableName, char *flag);

void updatePK(char *tableName, char *pk);


#endif
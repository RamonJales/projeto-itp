#ifndef SGDB_H
#define SGDB_H

int create_table(int colQty, char **colTyp, char **colNames, char pkName[], char tableName[]);

int insert(char tableName[], char **colValues);

#endif
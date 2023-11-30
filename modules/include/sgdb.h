#ifndef SGDB_H
#define SGDB_H

int create_table(int colQty, char **colNames, char pkName[], char tableName[]);

int insert(char tableName[], char **colValues);

void deleteTuple(char tableName[], char *primaryKey);

#endif
#include <stdbool.h>
#ifndef STRAUX_H
#define STRAUX_H

void cutOffEmptySpaces(char *str);

void extractStr(char *str, char *strDestiny, int position);

int countChar(char *str);

void putStrSufix(char *str, char *sufix, char *destiny);

void removeCharFromString(char *str, char ch);

void removeNumberFromStrInit(char *str);

void cutStrUntilFirstOccurrence(char *destiny, char *origin, char flag);

void cleanBuffer();

int levenshteinDistance(const char *s1, const char *s2);

bool isSimilar(const char *inputTableName, const char *existingTableName); 

void checkSimilarity(const char *inputTableName, const char *existingTables[], int numOfTables);

#endif
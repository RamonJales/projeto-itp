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

#endif
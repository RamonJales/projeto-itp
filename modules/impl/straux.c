#include "straux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void cutOffEmptySpaces(char *str) {
    int len = strlen(str);

    int i = 0;
    //encontra onde começa os caracteres da string
    while(i < len && isspace(str[i])) {
        i++;
    }

    //encontra o final da minha string
    int j = len;
    while(j > i && isspace(str[j-1])) {
        j--;
    }

    //move os caracteres para o inicio da sttring
    int k;
    for (k = 0; k < (j-i); k++) {
        str[k] = str[i+k];
    }

    //addicona caracter nulo
    str[k] = '\0';
    
}

void extractStr(char *str, char *strDestiny, int position) {
    int j = 0;
    if(position < strlen(str)) {
        while(str[position] != '\0') {
            strDestiny[j] = str[position];
            position++;
            j++;
        }
    }
    strDestiny[j] = '\0';
}

void cutStrUntilFirstOccurrence(char *destiny, char *origin, char flag) {
    // Encontrar a posição do caractere na string original
    char *position = strchr(origin, flag);

    if (position != NULL) {
        // Calcular o comprimento da substring até o caractere
        int comprimento = position - origin;

        // Copiar a substring para o destino
        strncpy(destiny, origin, comprimento);
        destiny[comprimento] = '\0'; // Adicionar o caractere nulo no final
    } else {
        // Se o caractere não for encontrado, copiar toda a string original
        strcpy(destiny, origin);
    }
}

//conta os caracteres válidos em uma string
int countChar(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        i++;
    }
}

void putStrSufix(char *str, char *sufix, char *destiny) {
    strcpy(destiny, str);
    strcat(destiny, sufix);
}

void removeCharFromString(char *str, char ch) {
    int len = strlen(str);
    char tmpStr[len];
    int i = 0;
    int j = 0;

    for (int i = 0; i < len; i++) {
        if(str[i] != ch) {
            tmpStr[j] = str[i];
            j++;  
        }
    }
    
    tmpStr[j] = '\0';
    strcpy(str, tmpStr);
}

void removeNumberFromStrInit(char *str) {
    int len = strlen(str);
    char tmpStr[len];
    int i = 0;
    int j = 0;

    for (int i = 0; i < len; i++) {
        if(isdigit(str[i]) == 0) {
            tmpStr[j] = str[i];
            j++;  
        }
    }

    tmpStr[j] = '\0';
    strcpy(str, tmpStr);
}

void cleanBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

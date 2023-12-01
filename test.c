#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgdb.h"

int main() {
    // int len = 2;

    // // char **v1 = (char**) malloc(len * sizeof(char *));
    // // v1[0] = strdup("s");
    // // v1[1] = strdup("s");

    // // char **v2 = (char**) malloc(len * sizeof(char *));
    // // v2[0] = strdup("name");
    // // v2[1] = strdup("password");

    // // char pk[] = "id";
    // char tname[100] = "test1";

    // // create_table(len, v1, v2, pk, tname);

    // char **v3 = (char**) malloc(len * sizeof(char *));
    // v3[0] = strdup("ramon");
    // v3[1] = strdup("1234");
    // insert(tname, v3);

    // for (int i = 0; i < len; i++) {
    //     // free(v1[i]);
    //     // free(v2[i]);
    //     free(v3[i]);
    // }

    // // free(v1);
    // // free(v2);
    // free(v3);

    //deleteTuple(tname, "2");

    searchDataFromTable("test1"); 
    return 0;
}
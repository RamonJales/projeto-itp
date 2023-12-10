#include <stdio.h>
#include <stdlib.h>
#include "funcaux.h"
#include "constant.h"

void freeMatrix(int colQty, char **matrix) {
    for (int i = 0; i < colQty; i++) {
        free(matrix[i]);
    }

    free(matrix);
}
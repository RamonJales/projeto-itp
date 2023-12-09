#include <stdio.h>
#include <stdlib.h>

void freeMatrix(int colQty, char **matrix) {
    for (int i = 0; i < colQty; i++) {
        free(matrix[i]);
    }

    free(matrix);
}
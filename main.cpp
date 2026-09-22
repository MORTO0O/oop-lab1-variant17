#include <iostream>
#include "matrix_ops.h"

int main() {
    int** matrix = matrix_create(2, 3);
    matrix[0][0] = 3;
    matrix[0][1] = 1;
    matrix[0][2] = 4;

    matrix[1][0] = 5;
    matrix[1][1] = 2;
    matrix[1][2] = 0;
    int* col_min = matrix_col_min(matrix, 2, 3);
    for (std::size_t i = 0; i < 3; ++i) {
        std::cout << col_min[i] << ' ';
    }

    std::cout << '\n';

    delete[] col_min;
    matrix_delete(matrix, 2);
    matrix = nullptr;
}
#pragma once

#include <cstddef>

int** matrix_create(
    std::size_t rows, 
    std::size_t cols
);

void matrix_delete(
    int** matrix, 
    std::size_t rows
);

void matrix_fill(
    int** matrix,
    std::size_t rows,
    std::size_t cols,
    int value
);

void matrix_print(
    const int* const* matrix,
    std::size_t rows,
    std::size_t cols
);

int* matrix_row_max(
    const int* const* matrix,
    std::size_t rows,
    std::size_t cols
);

int* matrix_col_min(
    const int* const* matrix,
    std::size_t rows,
    std::size_t cols
);

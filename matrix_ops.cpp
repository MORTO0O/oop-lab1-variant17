#include "matrix_ops.h"
#include <iostream>

int** matrix_create(std::size_t rows, std::size_t cols) {
    if (rows == 0 || cols == 0) return nullptr;

    int** matrix = new int*[rows]{};
    try {
        for (std::size_t i = 0; i < rows; i++){
            matrix[i] = new int[cols]{};
        }
    } catch (...) {
        matrix_delete(matrix, rows);
        throw;
    }

    return matrix;
}

void matrix_delete(int** matrix, std::size_t rows){
    if (matrix == nullptr) {
    return;
    }
    
    for (std::size_t i = 0; i < rows; i++){
        delete[] matrix[i];
    }

    delete[] matrix;
}

void matrix_fill(int** matrix, std::size_t rows, std::size_t cols, int value){
    if (matrix == nullptr) return;

    for(std::size_t i = 0; i < rows; i++){
        for(std::size_t j = 0; j < cols; j++){
            matrix[i][j] = value;
        }
    }
}

void matrix_print(const int* const* matrix, std::size_t rows, std::size_t cols){
    if (matrix == nullptr) return;

    for(std::size_t i = 0; i < rows; i++){
        for(std::size_t j = 0; j < cols; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << '\n';
    }
}

int* matrix_row_max(const int* const* matrix, std::size_t rows, std::size_t cols){
    if(matrix == nullptr || rows == 0 || cols == 0) return nullptr;

    int* results = new int[rows];

    for(std::size_t i = 0; i < rows; ++i){
        results[i] = matrix[i][0];

        for(std::size_t j = 1; j < cols; ++j){
            if(matrix[i][j] > results[i]){
                results[i] = matrix[i][j];
            }
        }
    }
    return results;
}

int* matrix_col_min(const int* const* matrix, std::size_t rows, std::size_t cols){
    if(matrix == nullptr || rows == 0 || cols == 0) return nullptr;

    int* results = new int[cols];

    for(std::size_t j = 0; j < cols; ++j){
        results[j] = matrix[0][j];

        for(std::size_t i = 1; i < rows; ++i){
            if(matrix[i][j] < results[j]){
                results[j] = matrix[i][j];
            }
        }
    }
    return results;
}

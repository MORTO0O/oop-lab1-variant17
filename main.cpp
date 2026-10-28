#include <iostream>
#include <limits>
#include <new>

#include "matrix_ops.h"

int main() {
    int** matrix = nullptr;
    std::size_t rows = 0;
    std::size_t cols = 0;

    for (;;) {
        std::cout << "1. Создать матрицу\n"
                  << "2. Заполнить значением\n"
                  << "3. Напечатать\n"
                  << "4. Максимумы строк и минимумы столбцов\n"
                  << "0. Выход\n";

        int choice = 0;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный пункт меню\n";
            continue;
        }

        switch (choice) {
            case 1: {
                long long new_rows = 0;
                long long new_cols = 0;
                std::cout << "Введите число строк и столбцов: ";
                if (!(std::cin >> new_rows >> new_cols) || new_rows <= 0 || new_cols <= 0) {
                    if (!std::cin) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    std::cout << "Некорректные размеры\n";
                    break;
                }

                try {
                    int** new_matrix = matrix_create(
                        static_cast<std::size_t>(new_rows),
                        static_cast<std::size_t>(new_cols)
                    );
                    matrix_fill(new_matrix, static_cast<std::size_t>(new_rows),
                                static_cast<std::size_t>(new_cols), 0);
                    matrix_delete(matrix, rows);
                    matrix = new_matrix;
                    rows = static_cast<std::size_t>(new_rows);
                    cols = static_cast<std::size_t>(new_cols);
                    std::cout << "Матрица создана\n";
                } catch (const std::bad_alloc&) {
                    std::cout << "Не удалось выделить память для матрицы\n";
                }
                break;
            }
            case 2: {
                if (matrix == nullptr) {
                    std::cout << "Сначала создайте матрицу\n";
                    break;
                }
                int value = 0;
                std::cout << "Введите значение: ";
                if (!(std::cin >> value)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректное значение\n";
                    break;
                }
                matrix_fill(matrix, rows, cols, value);
                std::cout << "Матрица заполнена\n";
                break;
            }
            case 3:
                if (matrix == nullptr) {
                    std::cout << "Сначала создайте матрицу\n";
                } else {
                    matrix_print(matrix, rows, cols);
                }
                break;
            case 4:
                if (matrix == nullptr) {
                    std::cout << "Сначала создайте матрицу\n";
                } else {
                    int* row_max = nullptr;
                    int* col_min = nullptr;
                    try {
                        row_max = matrix_row_max(matrix, rows, cols);
                        col_min = matrix_col_min(matrix, rows, cols);
                        std::cout << "Максимумы строк:";
                        for (std::size_t i = 0; i < rows; ++i) {
                            std::cout << ' ' << row_max[i];
                        }
                        std::cout << "\nМинимумы столбцов:";
                        for (std::size_t j = 0; j < cols; ++j) {
                            std::cout << ' ' << col_min[j];
                        }
                        std::cout << '\n';
                    } catch (const std::bad_alloc&) {
                        std::cout << "Не удалось выделить память для результата\n";
                    }
                    delete[] row_max;
                    delete[] col_min;
                }
                break;
            case 0:
                matrix_delete(matrix, rows);
                return 0;
            default:
                std::cout << "Неизвестный пункт меню\n";
                break;
        }
    }

    matrix_delete(matrix, rows);
    return 0;
}

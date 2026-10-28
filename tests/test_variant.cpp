#include <gtest/gtest.h>

#include "matrix_ops.h"

TEST(MatrixCreate, ZeroRows) {
    EXPECT_EQ(matrix_create(0, 3), nullptr);
}

TEST(MatrixCreate, ZeroColumns) {
    EXPECT_EQ(matrix_create(2, 0), nullptr);
}

TEST(MatrixCreate, InitializesElementsToZero) {
    int** matrix = matrix_create(2, 3);
    ASSERT_NE(matrix, nullptr);
    for (std::size_t i = 0; i < 2; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(matrix[i][j], 0);
        }
    }
    matrix_delete(matrix, 2);
}

TEST(MatrixDelete, AcceptsNull) {
    matrix_delete(nullptr, 2);
}

TEST(MatrixFill, FillsRectangularMatrix) {
    int** matrix = matrix_create(2, 3);
    ASSERT_NE(matrix, nullptr);
    matrix_fill(matrix, 2, 3, -7);
    for (std::size_t i = 0; i < 2; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(matrix[i][j], -7);
        }
    }
    matrix_delete(matrix, 2);
}

TEST(MatrixFill, AcceptsNull) {
    matrix_fill(nullptr, 2, 3, 7);
}

TEST(MatrixRowMax, OfficialExample) {
    const int first[] = {3, 1, 4};
    const int second[] = {5, 2, 0};
    const int* const matrix[] = {first, second};
    int* result = matrix_row_max(matrix, 2, 3);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 4);
    EXPECT_EQ(result[1], 5);
    delete[] result;
}

TEST(MatrixColMin, OfficialExample) {
    const int first[] = {3, 1, 4};
    const int second[] = {5, 2, 0};
    const int* const matrix[] = {first, second};
    int* result = matrix_col_min(matrix, 2, 3);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 0);
    delete[] result;
}

TEST(MatrixRowMax, NegativeElements) {
    const int first[] = {-9, -2, -5};
    const int second[] = {-4, -8, -6};
    const int* const matrix[] = {first, second};
    int* result = matrix_row_max(matrix, 2, 3);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], -2);
    EXPECT_EQ(result[1], -4);
    delete[] result;
}

TEST(MatrixColMin, NegativeElements) {
    const int first[] = {-9, -2};
    const int second[] = {-4, -8};
    const int* const matrix[] = {first, second};
    int* result = matrix_col_min(matrix, 2, 2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], -9);
    EXPECT_EQ(result[1], -8);
    delete[] result;
}

TEST(MatrixRowMax, SingleElement) {
    const int value[] = {42};
    const int* const matrix[] = {value};
    int* result = matrix_row_max(matrix, 1, 1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 42);
    delete[] result;
}

TEST(MatrixColMin, SingleElement) {
    const int value[] = {42};
    const int* const matrix[] = {value};
    int* result = matrix_col_min(matrix, 1, 1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 42);
    delete[] result;
}

TEST(MatrixRowMax, RejectsEmptyInput) {
    const int value[] = {1};
    const int* const matrix[] = {value};
    EXPECT_EQ(matrix_row_max(nullptr, 1, 1), nullptr);
    EXPECT_EQ(matrix_row_max(matrix, 0, 1), nullptr);
    EXPECT_EQ(matrix_row_max(matrix, 1, 0), nullptr);
}

TEST(MatrixColMin, RejectsEmptyInput) {
    const int value[] = {1};
    const int* const matrix[] = {value};
    EXPECT_EQ(matrix_col_min(nullptr, 1, 1), nullptr);
    EXPECT_EQ(matrix_col_min(matrix, 0, 1), nullptr);
    EXPECT_EQ(matrix_col_min(matrix, 1, 0), nullptr);
}

#include "matrix.h"

#include <gtest/gtest.h>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <utility>

static double sum_elements(const Matrix& matrix) {
    double sum = 0.0;
    for (std::size_t r = 0; r < matrix.rows(); ++r) {
        for (std::size_t c = 0; c < matrix.cols(); ++c) {
            sum += matrix.get(r, c);
        }
    }
    return sum;
}

TEST(MatrixTest, DefaultMatrixIsEmpty) {
    const Matrix matrix;
    EXPECT_EQ(matrix.rows(), 0);
    EXPECT_EQ(matrix.cols(), 0);
}

TEST(MatrixTest, SingletonRetainsFractionalValue) {
    const Matrix matrix(1, 1, -2.5);
    EXPECT_DOUBLE_EQ(matrix.get(0, 0), -2.5);
}

TEST(MatrixTest, SetsValuesAtDistinctPositions) {
    Matrix matrix(2, 3, 5.0);
    matrix.set(0, 2, 12.0);
    matrix.set(1, 0, -6.0);
    EXPECT_EQ(matrix.rows(), 2);
    EXPECT_EQ(matrix.cols(), 3);
    EXPECT_DOUBLE_EQ(matrix.get(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(matrix.get(0, 2), 12.0);
    EXPECT_DOUBLE_EQ(matrix.get(1, 0), -6.0);
}

TEST(MatrixTest, RejectsInvalidIndices) {
    Matrix matrix(2, 3);
    EXPECT_THROW(matrix.get(2, 0), std::out_of_range);
    EXPECT_THROW(matrix.set(0, 3, 1.0), std::out_of_range);
    EXPECT_THROW(Matrix().get(0, 0), std::out_of_range);
}

TEST(MatrixTest, CopyConstructorMakesIndependentBuffer) {
    Matrix original(2, 2, 4.0);
    Matrix copy(original);
    copy.set(1, 1, 7.0);
    EXPECT_DOUBLE_EQ(original.get(1, 1), 4.0);
    EXPECT_DOUBLE_EQ(copy.get(1, 1), 7.0);
}

TEST(MatrixTest, CopyAssignmentChangesShapeAndMakesIndependentBuffer) {
    Matrix original(2, 3, 4.0);
    Matrix copy(1, 1, 2.0);
    copy = original;
    original.set(1, 2, 9.0);
    EXPECT_EQ(copy.rows(), 2);
    EXPECT_EQ(copy.cols(), 3);
    EXPECT_DOUBLE_EQ(copy.get(1, 2), 4.0);
}

TEST(MatrixTest, CopyAssignmentFromEmptyClearsObject) {
    Matrix matrix(2, 2, 5.0);
    const Matrix empty;
    matrix = empty;
    EXPECT_EQ(matrix.rows(), 0);
    EXPECT_EQ(matrix.cols(), 0);
}

TEST(MatrixTest, MoveConstructorEmptiesSourceAndTransfersValues) {
    Matrix original(2, 1, 3.0);
    Matrix moved(std::move(original));
    EXPECT_DOUBLE_EQ(sum_elements(moved), 6.0);
    EXPECT_EQ(original.rows(), 0);
    EXPECT_EQ(original.cols(), 0);
    original = Matrix(1, 1, 5.0);
    EXPECT_DOUBLE_EQ(sum_elements(original), 5.0);
}

TEST(MatrixTest, MoveAssignmentReplacesOldBuffer) {
    Matrix original(2, 3, 6.0);
    Matrix moved(1, 1, 2.0);
    moved = std::move(original);
    EXPECT_DOUBLE_EQ(sum_elements(moved), 36.0);
    EXPECT_EQ(original.rows(), 0);
    EXPECT_EQ(original.cols(), 0);
}

TEST(MatrixTest, SelfCopyAndSelfMoveKeepValues) {
    Matrix matrix(2, 3, 5.0);
    Matrix& alias = matrix;
    matrix = alias;
    EXPECT_DOUBLE_EQ(sum_elements(matrix), 30.0);
    matrix = std::move(alias);
    EXPECT_DOUBLE_EQ(sum_elements(matrix), 30.0);
}

TEST(MatrixTest, AddsEqualShapesIncludingSelf) {
    Matrix matrix(2, 1, 1.5);
    matrix.add(Matrix(2, 1, -0.5));
    EXPECT_DOUBLE_EQ(matrix.get(1, 0), 1.0);
    matrix.add(matrix);
    EXPECT_DOUBLE_EQ(sum_elements(matrix), 4.0);
}

TEST(MatrixTest, RejectsIncompatibleAdditionAndKeepsValues) {
    Matrix matrix(2, 1, 2.0);
    EXPECT_THROW(matrix.add(Matrix(1, 2)), std::invalid_argument);
    EXPECT_DOUBLE_EQ(sum_elements(matrix), 4.0);
}

TEST(MatrixTest, MultipliesRectangularMatrices) {
    Matrix left(2, 3, 1.0);
    Matrix right(3, 4, 2.0);
    left.mul(right);
    EXPECT_EQ(left.rows(), 2);
    EXPECT_EQ(left.cols(), 4);
    EXPECT_DOUBLE_EQ(left.get(1, 3), 6.0);
    EXPECT_DOUBLE_EQ(sum_elements(left), 48.0);
}

TEST(MatrixTest, CanMultiplyBySelf) {
    Matrix matrix(2, 2);
    matrix.set(0, 1, 2.0);
    matrix.set(1, 0, 3.0);
    matrix.set(1, 1, 1.0);
    matrix.mul(matrix);
    EXPECT_DOUBLE_EQ(matrix.get(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(matrix.get(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(matrix.get(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(matrix.get(1, 1), 7.0);
}

TEST(MatrixTest, RejectsIncompatibleMultiplication) {
    Matrix matrix(2, 3, 2.0);
    EXPECT_THROW(matrix.mul(Matrix(2, 2)), std::invalid_argument);
    EXPECT_DOUBLE_EQ(sum_elements(matrix), 12.0);
}

TEST(MatrixTest, SupportsZeroInnerDimension) {
    Matrix matrix(2, 0);
    matrix.mul(Matrix(0, 3));
    EXPECT_EQ(matrix.rows(), 2);
    EXPECT_EQ(matrix.cols(), 3);
    EXPECT_DOUBLE_EQ(sum_elements(matrix), 0.0);
}

TEST(MatrixTest, RejectsOverflowingDimensions) {
    EXPECT_THROW(Matrix(std::numeric_limits<std::size_t>::max(), 2), std::length_error);
}

TEST(MatrixTest, PrintsInRowOrder) {
    Matrix matrix(2, 2);
    matrix.set(0, 0, 1.0);
    matrix.set(0, 1, 2.0);
    matrix.set(1, 0, 3.0);
    matrix.set(1, 1, 4.0);
    std::ostringstream stream;
    matrix.print(stream);
    EXPECT_EQ(stream.str(), "1 2\n3 4\n");
}

TEST(MatrixTest, ZeroPowerReturnsIdentity) {
    const Matrix result = Matrix(2, 2, 8.0).pow(0);
    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_DOUBLE_EQ(result.get(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result.get(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(result.get(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result.get(1, 1), 1.0);
}

TEST(MatrixTest, PowersAreComputedWithoutChangingSource) {
    Matrix matrix(2, 2);
    matrix.set(0, 0, 1.0);
    matrix.set(0, 1, 2.0);
    matrix.set(1, 0, 3.0);
    matrix.set(1, 1, 4.0);
    Matrix first = matrix.pow(1);
    first.set(0, 0, -1.0);
    const Matrix second = matrix.pow(2);
    const Matrix third = matrix.pow(3);
    EXPECT_DOUBLE_EQ(matrix.get(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(second.get(0, 0), 7.0);
    EXPECT_DOUBLE_EQ(second.get(0, 1), 10.0);
    EXPECT_DOUBLE_EQ(second.get(1, 0), 15.0);
    EXPECT_DOUBLE_EQ(second.get(1, 1), 22.0);
    EXPECT_DOUBLE_EQ(third.get(0, 0), 37.0);
    EXPECT_DOUBLE_EQ(third.get(1, 1), 118.0);
}

TEST(MatrixTest, RejectsPowersOfRectangularMatrices) {
    EXPECT_THROW(Matrix(2, 3).pow(2), std::invalid_argument);
    EXPECT_THROW(Matrix(2, 3).pow(0), std::invalid_argument);
}

TEST(MatrixTest, EmptySquareHasEmptyIdentity) {
    const Matrix result = Matrix().pow(0);
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
}

#include "matrix.h"

#include <limits>
#include <ostream>
#include <stdexcept>
#include <utility>

Matrix::Matrix(std::size_t rows, std::size_t cols, double initial)
    : rows_(rows), cols_(cols) {
    constexpr auto max_elements = std::numeric_limits<std::size_t>::max() / sizeof(double);
    if (rows != 0 && cols > max_elements / rows) {
        throw std::length_error("Matrix is too large");
    }

    const auto count = size();
    if (count != 0) {
        data_ = new double[count];
        for (std::size_t i = 0; i < count; ++i) {
            data_[i] = initial;
        }
    }
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
    const auto count = size();
    if (count != 0) {
        data_ = new double[count];
        for (std::size_t i = 0; i < count; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(std::exchange(other.rows_, 0)),
      cols_(std::exchange(other.cols_, 0)),
      data_(std::exchange(other.data_, nullptr)) {}

Matrix& Matrix::operator=(Matrix other) noexcept {
    swap(other);
    return *this;
}

Matrix::~Matrix() {
    delete[] data_;
}

void Matrix::swap(Matrix& other) noexcept {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(data_, other.data_);
}

std::size_t Matrix::rows() const noexcept { return rows_; }
std::size_t Matrix::cols() const noexcept { return cols_; }
std::size_t Matrix::size() const noexcept { return rows_ * cols_; }

std::size_t Matrix::index(std::size_t row, std::size_t col) const {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return row * cols_ + col;
}

double Matrix::get(std::size_t row, std::size_t col) const {
    return data_[index(row, col)];
}

void Matrix::set(std::size_t row, std::size_t col, double value) {
    data_[index(row, col)] = value;
}

void Matrix::add(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix sizes must match");
    }
    for (std::size_t i = 0; i < size(); ++i) {
        data_[i] += other.data_[i];
    }
}

void Matrix::mul(const Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Left columns must match right rows");
    }
    Matrix product(rows_, other.cols_);
    if (product.size() != 0 && cols_ != 0) {
        for (std::size_t row = 0; row < rows_; ++row) {
            for (std::size_t col = 0; col < other.cols_; ++col) {
                double value = 0.0;
                for (std::size_t k = 0; k < cols_; ++k) {
                    value += data_[row * cols_ + k] * other.data_[k * other.cols_ + col];
                }
                product.data_[row * other.cols_ + col] = value;
            }
        }
    }
    swap(product);
}

void Matrix::print(std::ostream& out) const {
    if (size() == 0) {
        return;
    }
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = 0; col < cols_; ++col) {
            if (col != 0) {
                out << ' ';
            }
            out << data_[row * cols_ + col];
        }
        out << '\n';
    }
}

Matrix Matrix::pow(std::size_t exponent) const {
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix must be square");
    }
    if (exponent == 0) {
        Matrix identity(rows_, cols_);
        for (std::size_t i = 0; i < rows_; ++i) {
            identity.data_[i * cols_ + i] = 1.0;
        }
        return identity;
    }
    Matrix result(*this);
    if (rows_ != 0) {
        for (std::size_t i = 1; i < exponent; ++i) {
            result.mul(*this);
        }
    }
    return result;
}

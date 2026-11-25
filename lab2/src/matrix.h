#pragma once

#include <cstddef>
#include <iosfwd>

class Matrix {
public:
    Matrix() noexcept = default;
    Matrix(std::size_t rows, std::size_t cols, double initial = 0.0);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix other) noexcept;
    ~Matrix();

    void swap(Matrix& other) noexcept;
    std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;
    double get(std::size_t row, std::size_t col) const;
    void set(std::size_t row, std::size_t col, double value);
    void add(const Matrix& other);
    void mul(const Matrix& other);
    void print(std::ostream& out) const;
    Matrix pow(std::size_t exponent) const;

private:
    std::size_t size() const noexcept;
    std::size_t index(std::size_t row, std::size_t col) const;

    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    double* data_ = nullptr;
};

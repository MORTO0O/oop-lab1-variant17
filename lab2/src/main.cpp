#include "matrix.h"

#include <iostream>

int main() {
    Matrix a(2, 2);
    a.set(0, 0, 1.0);
    a.set(0, 1, 2.0);
    a.set(1, 0, 3.0);
    a.set(1, 1, 4.0);
    std::cout << "A:\n";
    a.print(std::cout);
    const Matrix b(2, 2, 2.0);
    Matrix sum(a);
    sum.add(b);
    std::cout << "A + B:\n";
    sum.print(std::cout);

    Matrix product(a);
    product.mul(b);
    std::cout << "A * B:\n";
    product.print(std::cout);

    std::cout << "A^0:\n";
    a.pow(0).print(std::cout);
    std::cout << "A^2:\n";
    a.pow(2).print(std::cout);
}

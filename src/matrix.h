#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <string>

class matrix
{
public:
    using shape = std::pair<size_t,size_t>;
    using index = shape;
    static matrix dot(const matrix& lhs, const matrix& rhs);

private:
    const matrix::shape dim;

public:
    std::vector<double> data; // TODO add enough support to make data private

    matrix(const matrix::shape& _dim, const bool random_initialized=false);

    matrix::shape get_dim() const;

    double& operator()(const size_t i, const size_t j);
    double operator()(const size_t i, const size_t j) const;

    matrix dot(const matrix& rhs) const;
    matrix::index argmax() const;

    std::string to_string() const;
};

std::ostream& operator<<(std::ostream& target, const matrix::shape& dim);
std::ostream& operator<<(std::ostream& target, const matrix& mat);

matrix operator+(const matrix& lhs, const matrix& rhs);

#endif


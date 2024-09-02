#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class matrix
{
public:
    using shape = std::pair<size_t,size_t>;
    static matrix dot(const matrix& lhs, const matrix& rhs);

private:
    const matrix::shape dim;

public:
    std::vector<double> data; // TODO add enough support to make data private

    matrix(const size_t _m, const size_t _n);
    matrix(const matrix::shape& _dim);

    matrix::shape get_dim() const;

    double& operator()(const size_t i, const size_t j);
    double operator()(const size_t i, const size_t j) const;

    matrix dot(const matrix& rhs) const;
};

std::ostream& operator<<(std::ostream& target, const matrix::shape& dim);

matrix operator+(const matrix& lhs, const matrix& rhs);

#endif


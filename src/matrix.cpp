#include "matrix.h"

#include <stdexcept>
#include <algorithm>

#include "tdev.h"

matrix matrix::dot(const matrix& lhs, const matrix& rhs)
{
    const auto [lhs_m,lhs_n] = lhs.get_dim();
    const auto [rhs_m,rhs_n] = rhs.get_dim();
    if (lhs_n != rhs_m)
    {
        ERROR("Dimensions "<<lhs.get_dim()<<" and "<<rhs.get_dim()<<" don't line up for operation \'dot\'!");
        throw std::runtime_error("");
    }
    // primitive implementation
    return [&lhs,&rhs,&lhs_m,&lhs_n,&rhs_n]()
    {
        matrix temp(lhs_m, rhs_n);
        for (size_t i=0; i<lhs_m; ++i)
            for (size_t j=0; j<rhs_n; ++j)
                for (size_t k=0; k<lhs_n; ++k)
                    temp(i,j) += lhs(i,k) * rhs(k,j);
        return temp;
    }();
}

matrix::matrix(const size_t _m, const size_t _n)
    : dim({_m,_n})
    , data(std::vector<double>(_m*_n, 0.0))
{}

matrix::matrix(const matrix::shape& _dim)
    : dim(_dim)
    , data(std::vector<double>(_dim.first*_dim.second, 0.0))
{}

matrix::shape matrix::get_dim() const
{
    return dim;
}

double& matrix::operator()(const size_t i, const size_t j)
{
    return data[i*dim.second + j];
}

double matrix::operator()(const size_t i, const size_t j) const
{
    return data[i*dim.second + j];
}

matrix matrix::dot(const matrix& rhs) const
{
    return matrix::dot(*this, rhs);
}

std::ostream& operator<<(std::ostream& target, const matrix::shape& dim)
{
    target << "(" << dim.first << "," << dim.second << ")";
    return target;
}

matrix operator+(const matrix& lhs, const matrix& rhs)
{
    if (lhs.get_dim() != rhs.get_dim())
    {
        ERROR("Dimensions "<<lhs.get_dim()<<" and "<<rhs.get_dim()<<" don't line up for operation \'+\'!");
        throw std::runtime_error("");
    }
    return [&lhs, &rhs]()
    {
        matrix temp(rhs.get_dim());
        std::transform(lhs.data.begin(), lhs.data.end(), rhs.data.begin(),
            temp.data.begin(),
            [](const double lhs_val, const double rhs_val)
        {
            return lhs_val+rhs_val;
        });
        return temp;
    }();
}


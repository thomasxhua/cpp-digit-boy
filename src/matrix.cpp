#include "matrix.h"

#include <stdexcept>
#include <algorithm>
#include <random>
#include <sstream>
#include <iomanip>

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
        matrix temp({lhs_m, rhs_n});
        for (size_t i=0; i<lhs_m; ++i)
            for (size_t j=0; j<rhs_n; ++j)
                for (size_t k=0; k<lhs_n; ++k)
                    temp(i,j) += lhs(i,k) * rhs(k,j);
        return temp;
    }();
}

matrix::matrix(const matrix::shape& _dim, const bool random_initialized)
    : dim(_dim)
    , data(_dim.first * _dim.second)
{
    if (!random_initialized)
    {
        std::fill(data.begin(), data.end(), 0.0);
    }
    else
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);
        std::generate(data.begin(), data.end(), [&dis, &gen]() { return dis(gen); });
    }
}

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

matrix::index matrix::argmax() const
{
    const size_t i = std::distance(data.begin(), std::max_element(data.begin(), data.end()));
    return
    {
        i / dim.second,
        i % dim.second
    };
}

std::string matrix::to_string() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    uint64_t i = 0;
    std::for_each(data.begin(), data.end(), [this, &oss, &i](const double d)
    {
        oss << d << " " << (((i+++1)%dim.second==0) ? "\n" : "");
    });
    return oss.str();
}

std::ostream& operator<<(std::ostream& target, const matrix::shape& dim)
{
    target << "(" << dim.first << "," << dim.second << ")";
    return target;
}

std::ostream& operator<<(std::ostream& target, const matrix& mat)
{
    target << mat.to_string();
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


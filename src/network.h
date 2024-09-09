#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <mutex>

#include "mnist.h"
#include "matrix.h"

class network
{
private:
    std::vector<size_t> sizes;
    std::vector<matrix> weights;
    std::vector<matrix> biases;

    std::once_flag flag_init_weights_and_biases;
    void init_weights_and_biases();

public:
    network(const std::vector<size_t>& _sizes);
    
    matrix feedforward(const mnist::image& img) const;
    double test(const mnist::data& data) const;
};

double sigmoid(const double z);
matrix sigmoid(const matrix& mat);

#endif


#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <mutex>
#include <optional>

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
    
    double test(const mnist::data& data) const;

    void sgd(
        const mnist::data& training_data,
        const uint64_t epochs,
        const uint64_t mini_batch_size,
        const double eta,
        const std::optional<mnist::data>& test_data=std::nullopt);

};

double sigmoid(const double z);
matrix sigmoid(const matrix& mat);

#endif


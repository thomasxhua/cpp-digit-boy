#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <cstdint>
#include <tuple>

using matrix = std::vector<std::vector<double>>;

class network
{
private:
    std::vector<size_t> sizes;
    std::vector<matrix> weights;
    std::vector<matrix> biases;

    void init_weights_and_biases();

public:
    network(const std::vector<size_t>& _sizes);
};

#endif


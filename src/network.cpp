#include "network.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>

#include "tdev.h"

// http://neuralnetworksanddeeplearning.com/

void network::init_weights_and_biases()
{
    std::call_once(flag_init_weights_and_biases, [this]()
    {
        std::transform(std::next(sizes.begin()), sizes.end(),
            std::back_inserter(biases),
            [](const size_t layer_size)
        {
            return matrix({layer_size, 1}, true);
        });
        std::transform(sizes.begin(), std::prev(sizes.end()), std::next(sizes.begin()),
            std::back_inserter(weights),
            [](const size_t first_size, const size_t second_size)
        {
            return matrix({second_size, first_size}, true);
        });
    });
}

network::network(const std::vector<size_t>& _sizes)
    : sizes(_sizes)
{
    init_weights_and_biases();
}

double network::test(const mnist::data& data) const
{
    return 0;
#if 0
    const size_t correct = std::accumulate(data.begin(), data.end(),
        0ULL,
        [this](const size_t acc, const auto& entry)
    {
        const auto& lbl = entry.first;
        const auto& img = entry.second;
        const auto res  = feedforward(img);
        const auto ist  = res.argmax().second + 1;
        return acc + (ist == lbl);
    });
    return static_cast<double>(correct) / data.size();
#endif
}

void network::sgd(
    const mnist::data& training,
    const uint64_t epochs,
    const uint64_t mini_batch_size,
    const double eta,
    const std::optional<mnist::data>& test_data)
{
    if (test_data)
    {
        DELOG("Before training: " << test(test_data.value()));
    }
    // <training>
    for (const auto& [lbl,img] : training)
    {
        // layer i
        std::vector<matrix> as;
        std::vector<matrix> zs;
        // init layer 1
        as.push_back(img);
        for (size_t i=0; i<sizes.size()-1; ++i)
        {
            const matrix z = matrix::dot(weights[i], as.back()) + biases[i];
            const matrix a = sigmoid(z);
            as.push_back(a);
        }
    }
    // </training>
    if (test_data)
    {
        DELOG("After training:  " << test(test_data.value()));
    }
}

double sigmoid(const double z)
{
    return 1.0/(1.0+std::exp(z));
}

matrix sigmoid(const matrix& mat)
{
    return matrix::map(mat, static_cast<double(*)(double)>(sigmoid));
}


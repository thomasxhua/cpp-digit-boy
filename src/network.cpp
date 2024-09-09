#include "network.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>

#include "tdev.h"

void network::init_weights_and_biases()
{
    std::call_once(flag_init_weights_and_biases, [this]()
    {
        std::transform(std::next(sizes.begin()), sizes.end(),
            std::back_inserter(biases),
            [](const size_t layer_size)
        {
            return matrix({1, layer_size}, true);
        });
        std::transform(sizes.begin(), std::prev(sizes.end()), std::next(sizes.begin()),
            std::back_inserter(weights),
            [](const size_t first_size, const size_t second_size)
        {
            return matrix({first_size, second_size}, true);
        });
    });
}

network::network(const std::vector<size_t>& _sizes)
    : sizes(_sizes)
{
    init_weights_and_biases();
}

matrix network::feedforward(const mnist::image& img) const
{
    // layer 1 (TODO make image into matrix)
    size_t layer_num = 0;
    const matrix layer_1 = [this, &layer_num, &img]()
    {
        matrix temp({1, sizes[layer_num++]});
        std::transform(img.begin(), img.end(), temp.data.begin(), [](const mnist::pixel p)
        {
            return static_cast<double>(p) / std::numeric_limits<mnist::pixel>::max();
        });
        return temp;
    }();
    // layer 2
    size_t weights_num = 0;
    size_t biases_num = 0;
    const matrix layer_2 = sigmoid(layer_1.dot(weights[weights_num++]) + biases[biases_num++]);
    // layer 3
    const matrix layer_3 = sigmoid(layer_2.dot(weights[weights_num++]) + biases[biases_num++]);
    return layer_3;
}

double network::test(const mnist::data& data) const
{
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
}

double sigmoid(const double z)
{
    return 1.0/(1.0+std::exp(z));
}

matrix sigmoid(const matrix& mat)
{
    return [&mat]()
    {
        matrix temp(mat.get_dim());
        std::transform(mat.data.begin(), mat.data.end(),
            temp.data.begin(),
            [](const double z)
        {
            return sigmoid(z);
        });
        return temp;
    }();
}


#include "network.h"

#include <algorithm>
#include <random>

#include "tdev.h"

void network::init_weights_and_biases()
{
    std::transform(std::next(sizes.begin()), sizes.end(),
        std::back_inserter(biases),
        [](const size_t layer_size)
    {
        return matrix(1, layer_size);
    });
    std::transform(sizes.begin(), std::prev(sizes.end()), std::next(sizes.begin()),
        std::back_inserter(weights),
        [](const size_t first_size, const size_t second_size)
    {
        return matrix(first_size, second_size);
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
        matrix temp(1, sizes[layer_num++]);
        std::transform(img.begin(), img.end(), temp.data.begin(), [](const mnist::pixel p)
        {
            return static_cast<double>(p);
        });
        return temp;
    }();
    // layer 2
    size_t weights_num = 0;
    size_t biases_num = 0;
    const matrix layer_2 = layer_1.dot(weights[weights_num++]) + biases[biases_num++];
    // layer 3
    const matrix layer_3 = layer_2.dot(weights[weights_num++]) + biases[biases_num++];
    return layer_3;
}


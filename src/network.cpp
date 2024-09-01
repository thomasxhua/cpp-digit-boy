#include "network.h"

#include "tdev.h"

void network::init_weights_and_biases()
{
    for (auto it=sizes.begin(); it!=sizes.end(); ++it)
    {
        if (it != sizes.begin())
        {
            biases.push_back(matrix(*it, std::vector<double>(1, 0)));
        }
        const auto next_it = std::next(it);
        if (next_it != sizes.end())
        {
            weights.push_back(matrix(*it, std::vector<double>(*next_it, 0)));
        }
    }
}

network::network(const std::vector<size_t>& _sizes)
    : sizes(_sizes)
{
    init_weights_and_biases();
    //for (const auto& m : weights)
    //    DELOG(m.size() << ", " << m[0].size());
    //for (const auto& m : biases)
    //    DELOG(m.size() << ", " << m[0].size());
}


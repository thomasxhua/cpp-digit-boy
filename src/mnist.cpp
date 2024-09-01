#include "mnist.h"

#include "tdev.h"

#include <fstream>
#include <bit>
#include <algorithm>
#include <numeric>

uint32_t mnist::from_ifstream_read_32(std::ifstream& ifs)
{
    uint32_t word;
    ifs.read(reinterpret_cast<char*>(&word), sizeof word);
    return std::byteswap(word);
}

uint8_t mnist::from_ifstream_read_8(std::ifstream& ifs)
{
    uint8_t word;
    ifs.read(reinterpret_cast<char*>(&word), sizeof word);
    return std::byteswap(word);
}

std::string mnist::image_to_str(const mnist::image& img)
{
    return std::accumulate(img.begin(), img.end(), std::string(), [](const std::string& acc, const auto& row)
    {
        return acc + std::accumulate(row.begin(), row.end(), std::string(), [](const std::string& acc_row, const auto& col)
        {
            return acc_row + (col ? " X" : " .");
        }) + "\n";
    });
}

// https://yann.lecun.com/exdb/mnist/

#define LBLS_MAGIC_NUM 0x801
#define IMGS_MAGIC_NUM 0x803

mnist::data mnist::read_data_from_files(const std::string& imgs_file, const std::string& lbls_file)
{
    std::vector<mnist::entry> data{};
    // load imgs
    std::ifstream imgs_ifs(imgs_file, std::ios::binary);
    if (!imgs_ifs.is_open())
    {
        ERROR("Cannot open \'" << imgs_file << "\'!");
        return {};
    }
    const uint32_t imgs_magic_num = mnist::from_ifstream_read_32(imgs_ifs);
    const uint32_t imgs_num_items = mnist::from_ifstream_read_32(imgs_ifs);
    const uint32_t imgs_num_rows  = mnist::from_ifstream_read_32(imgs_ifs);
    const uint32_t imgs_num_cols  = mnist::from_ifstream_read_32(imgs_ifs);
    // load lbls
    std::ifstream lbls_ifs(lbls_file, std::ios::binary);
    if (!lbls_ifs.is_open())
    {
        ERROR("Cannot open \'" << lbls_file << "\'!");
        return {};
    }
    const uint32_t lbls_magic_num = mnist::from_ifstream_read_32(lbls_ifs);
    const uint32_t lbls_num_items = mnist::from_ifstream_read_32(lbls_ifs);
    // sanity checks
    if (imgs_magic_num != IMGS_MAGIC_NUM
        || imgs_num_rows != MNIST_IMG_SIZE
        || imgs_num_cols != MNIST_IMG_SIZE
        || lbls_magic_num != LBLS_MAGIC_NUM
        || lbls_num_items != imgs_num_items)
    {
        ERROR("Something went wrong!");
        return {};
    }
    for (uint32_t i=0; i<imgs_num_items; ++i)
    {
        const mnist::label lbl = mnist::from_ifstream_read_8(lbls_ifs);
        const mnist::image img = [&imgs_ifs]()
        {
            mnist::image temp{};
            std::transform(temp.begin(), temp.end(), temp.begin(), [&imgs_ifs](auto& row)
            {
                std::generate(row.begin(), row.end(), [&imgs_ifs]()
                {
                    return mnist::from_ifstream_read_8(imgs_ifs);
                });
                return row;
            });
            return temp;
        }();
        data.push_back({lbl, img});
    }
    return data;
}

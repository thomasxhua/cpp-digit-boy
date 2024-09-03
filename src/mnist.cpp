#include "mnist.h"

#include "tdev.h"

#include <fstream>
#include <bit>
#include <algorithm>
#include <numeric>
#include <stdexcept>

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

std::string mnist::image_to_string(const mnist::image& img)
{
    return std::accumulate(img.begin(), img.end(), std::string(), [i=0](const std::string& acc, const auto& entry) mutable
    {
        return acc
            + (entry ? " X" : " .")
            + (++i % MNIST_IMG_SIZE == 0 ? "\n" : "");
    });
}

std::ostream& operator<<(std::ostream& target, const mnist::image& img)
{
    target << mnist::image_to_string(img);
    return target;
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
        throw std::runtime_error("");
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
        throw std::runtime_error("");
    }
    for (uint32_t i=0; i<imgs_num_items; ++i)
    {
        const mnist::label lbl = mnist::from_ifstream_read_8(lbls_ifs);
        const mnist::image img = [&imgs_ifs]()
        {
            mnist::image temp{};
            std::for_each(temp.begin(), temp.end(), [&imgs_ifs](auto& pxl)
            {
                pxl = mnist::from_ifstream_read_8(imgs_ifs);
            });
            return temp;
        }();
        data.push_back({lbl, img});
    }
    return data;
}

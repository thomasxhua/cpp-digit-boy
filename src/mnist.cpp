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
    return std::accumulate(
        img.data.begin(), img.data.end(),
        std::string(),
        [i=0](const std::string& acc, const auto& entry) mutable
    {
        return acc
            + (entry ? " X" : " .")
            + (++i % MNIST_IMG_SIZE == 0 ? "\n" : "");
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
        throw std::runtime_error(STR("Cannot open \'" << imgs_file << "\'!"));
    }
    const uint32_t imgs_magic_num = mnist::from_ifstream_read_32(imgs_ifs);
    const uint32_t imgs_num_items = mnist::from_ifstream_read_32(imgs_ifs);
    const uint32_t imgs_num_rows  = mnist::from_ifstream_read_32(imgs_ifs);
    const uint32_t imgs_num_cols  = mnist::from_ifstream_read_32(imgs_ifs);
    // load lbls
    std::ifstream lbls_ifs(lbls_file, std::ios::binary);
    if (!lbls_ifs.is_open())
    {
        throw std::runtime_error(STR("Cannot open \'" << lbls_file << "\'!"));
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
        throw std::runtime_error(STR("Something went wrong!"));
    }
    for (uint32_t i=0; i<imgs_num_items; ++i)
    {
        const mnist::label lbl = mnist::from_ifstream_read_8(lbls_ifs);
        const mnist::image img = [&imgs_ifs]()
        {
            mnist::image_raw raw{};
            std::for_each(raw.begin(), raw.end(), [&imgs_ifs](auto& pxl)
            {
                pxl = mnist::from_ifstream_read_8(imgs_ifs);
            });
            return [&raw]()
            {
                matrix temp({MNIST_IMG_SIZE*MNIST_IMG_SIZE, 1});
                std::transform(raw.begin(), raw.end(), temp.data.begin(), [](const mnist::pixel p)
                {
                    return static_cast<double>(p) / std::numeric_limits<mnist::pixel>::max();
                });
                return temp;
            }();
        }();
        data.push_back({lbl, img});
    }
    return data;
}


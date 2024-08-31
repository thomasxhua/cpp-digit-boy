#include "mnist.h"

#include "tdev.h"

#include <fstream>
#include <bit>

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

mnist::data mnist::read_data_from_files(const std::string& imgs_file, const std::string& lbls_file)
{
    std::vector<mnist::entry> data{};
    std::ifstream ifs(imgs_file, std::ios::binary);
    if (!ifs.is_open())
    {
        ERROR("Cannot open \'" << imgs_file << "\'!");
        return {};
    }
    DEVAR(mnist::from_ifstream_read_32(ifs));
    DEVAR(mnist::from_ifstream_read_32(ifs));
    return data;
}

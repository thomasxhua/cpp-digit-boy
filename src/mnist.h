#ifndef MNIST_H
#define MNIST_H

#include <array>
#include <vector>
#include <cstdint>
#include <string>

// https://yann.lecun.com/exdb/mnist/

namespace mnist
{

#define MNIST_IMAGE_SIZE 28

using label = uint8_t;
using pixel = uint8_t;
using image = std::array<std::array<mnist::pixel, MNIST_IMAGE_SIZE>, MNIST_IMAGE_SIZE>;

using entry = std::pair<mnist::label, mnist::image>;
using data  = std::vector<mnist::entry>;

uint32_t from_ifstream_read_32(std::ifstream& ifs);
uint8_t from_ifstream_read_8(std::ifstream& ifs);

mnist::data read_data_from_files(const std::string& imgs_file, const std::string& lbls_file);

}

#endif


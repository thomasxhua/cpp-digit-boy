#ifndef MNIST_H
#define MNIST_H

#include <array>
#include <vector>
#include <cstdint>
#include <string>

namespace mnist
{

#define MNIST_IMG_SIZE 28
#define MNIST_OUT_SIZE 10

using label = uint8_t;
using pixel = uint8_t;
using image = std::array<mnist::pixel, MNIST_IMG_SIZE*MNIST_IMG_SIZE>;

using entry = std::pair<mnist::label, mnist::image>;
using data  = std::vector<mnist::entry>;

uint32_t from_ifstream_read_32(std::ifstream& ifs);
uint8_t from_ifstream_read_8(std::ifstream& ifs);

std::string image_to_str(const mnist::image& img);

mnist::data read_data_from_files(const std::string& imgs_file, const std::string& lbls_file);


}

#endif


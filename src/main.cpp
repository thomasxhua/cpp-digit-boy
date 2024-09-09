#include <iomanip>
#include <algorithm>

#include "tdev.h"
#include "mnist.h"
#include "network.h"

#define IMGS_60K "res/train-images-idx3-ubyte"
#define LBLS_60K "res/train-labels-idx1-ubyte"
#define IMGS_10K "res/t10k-images-idx3-ubyte"
#define LBLS_10K "res/t10k-labels-idx1-ubyte"

int main()
{
    //const mnist::data training = mnist::read_data_from_files(IMGS_60K, LBLS_60K);
    const mnist::data test     = mnist::read_data_from_files(IMGS_10K, LBLS_10K);
    network net({MNIST_IMG_SIZE*MNIST_IMG_SIZE,15,MNIST_OUT_SIZE});
    DEVAR(net.test(test));
    return 0;
}


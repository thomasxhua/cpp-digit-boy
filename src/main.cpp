#include "mnist.h"
#include "network.h"

#include "tdev.h"

#define IMGS_60K "res/train-images-idx3-ubyte"
#define LBLS_60K "res/train-labels-idx1-ubyte"
#define IMGS_10K "res/t10k-images-idx3-ubyte"
#define LBLS_10K "res/t10k-labels-idx1-ubyte"

int main()
{
    const mnist::data training = mnist::read_data_from_files(IMGS_60K, LBLS_60K);
    network net({MNIST_IMG_SIZE*MNIST_IMG_SIZE,15,MNIST_OUT_SIZE});

    return 0;
}


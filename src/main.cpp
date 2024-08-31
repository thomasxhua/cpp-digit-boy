#include "mnist.h"

#define IMGS_60K "res/train-images-idx3-ubyte"
#define LBLS_60K "res/train-labels-idx3-ubyte"
#define IMGS_10K "res/t10k-images-idx3-ubyte"
#define LBLS_10K "res/t10k-labels-idx3-ubyte"

int main()
{
    const mnist::data training = mnist::read_data_from_files(IMGS_60K, LBLS_60K);

    return 0;
}


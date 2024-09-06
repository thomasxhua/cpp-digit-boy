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
    const mnist::data training = mnist::read_data_from_files(IMGS_60K, LBLS_60K);
    network net({MNIST_IMG_SIZE*MNIST_IMG_SIZE,15,MNIST_OUT_SIZE});
    DEVAR(net.test(training));
#if 1
    uint64_t correct = 0;
    for (const auto& [lbl,img] : training)
    {
        const auto res = net.feedforward(img);
        const auto ist = res.argmax().second + 1;
        correct += (ist == lbl);
        //PRINT(mnist::image_to_string(img));
        //DEVAR(uint64_t(lbl));
        //PRINT(res);
        //DEVAR(ist);
        //DEVAR((ist == lbl));
        //PAUSE();
    }
    DEVAR(std::pair(correct,training.size()));
#else
    // TESTING MATRIX DOT
    matrix a({3,4});
    matrix b({4,3});
    std::for_each(a.data.begin(), a.data.end(), [i=1](double& d) mutable { d=i++; });
    std::for_each(b.data.begin(), b.data.end(), [i=1](double& d) mutable { d=i++; });
    const auto c = a.dot(b);
    DEVAR("\n"<<a.to_string());
    DEVAR("\n"<<b.to_string());
    DEVAR("\n"<<c.to_string());
    DEVAR(a.argmax());
    DEVAR(b.argmax());
    DEVAR(c.argmax());
#endif

    return 0;
}


#include "secuencial1.h"

std::vector<int> Sequential1::calculate(const int* input, const int buckets,
                                       const int input_size) {
    int* histogram = new int[buckets]();

    for(int idx = 0; idx < input_size; idx++) {
      histogram[input[idx] - 1]++;
    }

    std::vector<int> result(histogram, histogram + buckets);
    
    delete[] histogram;

    return result;
}

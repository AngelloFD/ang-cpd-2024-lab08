#include "openmp_atomic.h"
#include <atomic>

std::vector<int> OpenMPAtomic::calculate(const int* input, const int buckets, const int input_size) {
    std::vector<std::atomic<int>> histogram(buckets);

    #pragma omp parallel for
    for(int idx = 0; idx < input_size; idx++) {
      histogram[input[idx] - 1]++;
    }

    std::vector<int> result(buckets);
    for (int i = 0; i < buckets; i++) {
        result[i] = histogram[i];
    }

    return result;
}
#include "openmp_ompatomic.h"
#include <mutex>
std::vector<int> OpenMPOMPAtomic::calculate(const int* input, const int buckets, const int input_size) {
    std::vector<int> histogram(buckets, 0);  
    std::mutex mtx;

    #pragma omp parallel for
    for(int idx = 0; idx < input_size; idx++) {
        #pragma omp atomic
        histogram[input[idx] - 1]++;
    }
    return histogram;
}
#include "openmp_lock_unlock.h"
#include <mutex>
std::vector<int> OpenMPLockUnlock::calculate(const int* input, const int buckets, const int input_size) {
    std::vector<int> histogram(buckets, 0);  
    std::mutex mtx;

    #pragma omp parallel for
    for(int idx = 0; idx < input_size; idx++) {
        mtx.lock();
        histogram[input[idx] - 1]++;
        mtx.unlock();
    }
    return histogram;
}
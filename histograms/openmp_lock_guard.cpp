#include "openmp_lock_guard.h"
#include <mutex>
std::vector<int> OpenMPLockGuard::calculate(const int* input, const int buckets, const int input_size) {
    std::vector<int> histogram(buckets, 0);  
    std::mutex mtx;

    #pragma omp parallel for
    for(int idx = 0; idx < input_size; idx++) {
      std::lock_guard<std::mutex> lock(mtx);
      histogram[input[idx] - 1]++;
    }
  

    return histogram;
}
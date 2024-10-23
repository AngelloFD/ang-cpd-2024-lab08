#include "openmp_reduction.h"

std::vector<int> OpenMPReduction::calculate(const int* input, const int buckets, const int input_size) {
    int* histogram = new int[buckets](); 
    #pragma omp parallel for reduction(+ : histogram[ : buckets])
    for(int idx = 0; idx < input_size; idx++) {
      histogram[input[idx] - 1]++;
    }
    std::vector<int> result(histogram, histogram + buckets);
    
    delete[] histogram;

    return result;
}
#include "openmp_reduction.h"
#include <vector>

std::vector<int> OpenMPReduction::calculate(const int* input, const int buckets, const int input_size) {
    std::vector<int> histogram(buckets, 0);  
    #pragma omp parallel for reduction(+ : histograma[ : MAXIMO_VALOR])
    for(int idx = 0; idx < input_size; idx++) {
      histogram[input[idx] - 1]++;
    }

    return histogram;
}
#ifndef ESTANDAR_REDUCTION_H
#define ESTANDAR_REDUCTION_H

#include "histogram.h"

class EstandarReduction : public Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
  // static void calcular_local_histograma(std::vector<int>& local_histograma, int inicio, int fin, const int* input);
};

#endif

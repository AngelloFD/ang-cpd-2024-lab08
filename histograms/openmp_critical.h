#ifndef OPENMP_CRITICAL_H
#define OPENMP_CRITICAL_H

#include "histogram.h"

class OpenMPCritical : public Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
};

#endif

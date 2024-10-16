#ifndef OPENMP_OMPATOMIC_H
#define OPENMP_OMPATOMIC_H

#include "histogram.h"

class OpenMPOMPAtomic : public Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
};

#endif

#ifndef SEQUENTIAL1_H
#define SEQUENTIAL1_H

#include "histogram.h"

class Sequential1 : Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
};

#endif 

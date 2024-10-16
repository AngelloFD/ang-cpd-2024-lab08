#ifndef OPENMP_LOCK_UNLOCK_H
#define OPENMP_LOCK_UNLOCK_H

#include "histogram.h"

class OpenMPLockUnlock : public Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
};

#endif

#include <gtest/gtest.h>

#include <random>

#include "secuencial1.h"
#include "sequential.h"
#include "estandar.h"
#include "estandar_reduction.h"
#include "openmp_atomic.h"
#include "openmp_reduction.h"
#include "openmp_lock_guard.h"
#include "openmp_lock_unlock.h"
#include "openmp_critical.h"
#include "openmp_ompatomic.h"

static int* randomInput = nullptr;
static const int MAXIMO_VALOR = 5;
static const int NUMERO_ELEMENTOS = 100000000;

void inicializa() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> uni_dis(1, MAXIMO_VALOR);

  if(randomInput == nullptr) {
    randomInput = new int[NUMERO_ELEMENTOS];
    for(int i = 0; i < NUMERO_ELEMENTOS; ++i) {
      randomInput[i] = uni_dis(gen);
    }
  }
}

void finaliza() {
  if(randomInput != nullptr) {
    delete[] randomInput;
    randomInput = nullptr;
  }
}

TEST(SequentialTest, pruebaOK) {
  Sequential1 histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(Sequential2Test, pruebaOK) {
  Sequential histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(EstandarTest, pruebaOK) {
  Estandar histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(EstandarReductionTest, pruebaOK) {
  EstandarReduction histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPAtomicTest, pruebaOK) {
  OpenMPAtomic histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPReductionTest, pruebaOK) {
  OpenMPReduction histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPLockGuardTest, pruebaOK) {
  OpenMPLockGuard histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPLockUnlockTest, pruebaOK) {
  OpenMPLockUnlock histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPCriticalTest, pruebaOK) {
  OpenMPCritical histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPOMPAtomicTest, pruebaOK) {
  OpenMPOMPAtomic histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

int main(int argc, char** argv) {
  inicializa();
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  finaliza();
  return ret;
}

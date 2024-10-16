#include <benchmark/benchmark.h>

#include <mutex>
#include <new>
#include <random>
#include <thread>

#include "sequential.h"

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

static void BM_secuencial(benchmark::State& state) {
  int histograma[MAXIMO_VALOR] = {0};

  for(auto _ : state) {
    for(int idx = 0; idx < NUMERO_ELEMENTOS; idx++) {
      histograma[randomInput[idx] - 1]++;
    }
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_secuencial2(benchmark::State& state) {
  Sequential histogramCalculator;

  for(auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                    NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

std::mutex mtx_estandar;
void calcular_histograma(int* histograma, int inicio, int fin) {
  for(int idx = inicio; idx < fin; idx++) {
    std::lock_guard<std::mutex> lock(mtx_estandar);
    histograma[randomInput[idx] - 1]++;
  }
}

void histograma_estandar() {
  int histograma[MAXIMO_VALOR] = {0};
  const int num_hilos = std::thread::hardware_concurrency();
  std::vector<std::thread> hilos(num_hilos);
  int chunk = NUMERO_ELEMENTOS / num_hilos;

  for(int idx = 0; idx < num_hilos; idx++) {
    int inicio = chunk * idx;
    int fin = (idx == num_hilos - 1) ? NUMERO_ELEMENTOS : idx * chunk;
    hilos[idx] =
        std::thread(calcular_histograma, std::ref(histograma), inicio, fin);
  }

  for(auto& hilo : hilos) {
    hilo.join();
  }
}

static void BM_estandar(benchmark::State& state) {
  for(auto _ : state) {
    histograma_estandar();
  }
}

static void BM_estandar_reduction(benchmark::State& state) {
  EstandarReduction histogramCalculator;

  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

static void BM_openmp_reduction(benchmark::State& state) {
  OpenMPReduction histogramCalculator;

  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

static void BM_openmp_atomic(benchmark::State& state) {
  OpenMPAtomic histogramCalculator;

  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

static void BM_openmp_lock_guard(benchmark::State& state) {
  OpenMPLockGuard histogramCalculator;

  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

static void BM_openmp_lock_unlock(benchmark::State& state) {
  OpenMPLockUnlock histogramCalculator;

  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

static void BM_openmp_critical(benchmark::State& state) {
  OpenMPCritical histogramCalculator;

  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

static void BM_openmp_ompatomic(benchmark::State& state) {
  OpenMPOMPAtomic histogramCalculator;

  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

BENCHMARK(BM_secuencial)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_secuencial2)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_estandar)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_estandar_reduction)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_atomic)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_reduction)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_lock_guard)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_lock_unlock)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_critical)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_ompatomic)->UseRealTime()->Unit(benchmark::kMillisecond);

int main(int argc, char** argv) {
  inicializa();
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  finaliza();
}

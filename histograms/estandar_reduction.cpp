#include "estandar_reduction.h"
#include <thread>

void calcular_local_histograma(std::vector<int>& local_histograma, int inicio, int fin, const int* input) {
  for(int idx = inicio; idx < fin; idx++) {
    local_histograma[input[idx] - 1]++;
  }
}
// void EstandarReduction::calcular_local_histograma(std::vector<int>& local_histograma, int inicio, int fin, const int* input) {
//   for(int idx = inicio; idx < fin; idx++) {
//     local_histograma[input[idx] - 1]++;
//   }
// }

std::vector<int> EstandarReduction::calculate(const int* input, const int buckets, const int input_size) {
  std::vector<int> histogram(buckets, 0);
  const int num_hilos = std::thread::hardware_concurrency();

  std::vector<std::vector<int>> local_histograma(num_hilos, std::vector<int>(buckets, 0));
  std::vector<std::thread> hilos(num_hilos);
  int chunk = input_size / num_hilos;

  for(int idx = 0; idx < num_hilos; idx++) {
    int inicio = chunk * idx;
    int fin = (idx == num_hilos - 1) ? input_size : idx * chunk;
    // hilos[idx] = std::thread(EstandarReduction::calcular_local_histograma, std::ref(local_histograma[idx]), inicio, fin, std::cref(input));
    hilos[idx] = std::thread(calcular_local_histograma, std::ref(local_histograma[idx]), inicio, fin, std::cref(input));
  }

  for(auto& hilo : hilos) {
    hilo.join();
  }

  for(int idx = 0; idx < num_hilos; idx++) {
    for(int idy = 0; idy < num_hilos; idy++) {
      histogram[idy] += local_histograma[idx][idy];
    }
  }

  return histogram;
}

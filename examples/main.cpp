#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include "QuantumSearch.h"

int main() {
    constexpr size_t data_size = 10000;
    std::vector<double> data(data_size);

    // Filling with random doubles
    std::mt19937 gen(42);
    std::uniform_real_distribution<> dist(0.0, 10000.0);
    for (auto& val : data) val = dist(gen);

    // Selecting a random index and target value
    std::uniform_int_distribution<> index_dist(0, data_size - 1);
    size_t target_index = index_dist(gen);
    double target_value = data[target_index];

    std::cout << "Target value: " << target_value << " at index " << target_index << "\n";

    // Standard search
    auto start_std = std::chrono::high_resolution_clock::now();
    auto it = std::find(data.begin(), data.end(), target_value);
    auto end_std = std::chrono::high_resolution_clock::now();

    int std_index = (it != data.end()) ? static_cast<int>(std::distance(data.begin(), it)) : -1;
    std::chrono::duration<double> duration_std = end_std - start_std;
    std::cout << "[std::find] Found at index: " << std_index
              << " | Time: " << duration_std.count() << " seconds\n";

    // Quantum search
    auto start_q = std::chrono::high_resolution_clock::now();
    int quantum_index = quantum::grover_search(data, target_value, 100);
    auto end_q = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration_q = end_q - start_q;
    std::cout << "[Grover search] Found at index: " << quantum_index
              << " | Time: " << duration_q.count() << " seconds\n";

}

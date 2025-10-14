#include "utils.h"
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

auto measure_time(const std::function<void()>& func) -> double {
    const auto start = std::chrono::high_resolution_clock::now();
    func();
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

auto generate_random_data(size_t size) -> std::vector<int> {
    std::vector<int> data(size);
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 999);
    std::generate(data.begin(), data.end(), [&]() { return dist(gen); });
    return data;
}
// Compiler: g++ (C++20)

#include "performance_study.h"
#include <vector>
#include <cmath>
#include <functional>

int main() {
    auto fast_op = [](int& n) {
        n = (n * 3 + 17) % 1000;
    };

    auto slow_op = [](int& n) {
        double result = 0;
        for (int i = 0; i < 200; ++i) {
            result += std::sin(static_cast<double>(n) * i) * std::cos(static_cast<double>(n));
        }
        n = static_cast<int>(result) % 1000;
    };

    const std::vector<size_t> data_sizes = {100'000, 1'000'000, 5'000'000};

    for (const auto size : data_sizes) {
        run_performance_study("Fast Operation", fast_op, size);
        run_performance_study("Slow Operation", slow_op, size);
    }

    return 0;
}

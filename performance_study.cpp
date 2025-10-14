#include "performance_study.h"
#include "utils.h"
#include "custom_parallel.h"

#include <iostream>
#include <vector>
#include <execution>
#include <iomanip>
#include <thread>

void run_performance_study(const std::string& operation_name, const std::function<void(int&)>& operation, size_t data_size) {
    std::cout << "\n";
    std::cout << "Study for operation: '" << operation_name << "' on " << data_size << " elements\n";
    std::cout << "\n\n";

    auto original_data = generate_random_data(data_size);

    std::cout << "1. Standard Library Algorithms \n";
    auto data_copy = original_data;
    double seq_time = measure_time([&]() {
        std::for_each(data_copy.begin(), data_copy.end(), operation);
    });
    std::cout << "Sequential (no policy): " << std::fixed << std::setprecision(3) << seq_time << " ms\n";

    data_copy = original_data;
    double par_time = measure_time([&]() {
        std::for_each(std::execution::par, data_copy.begin(), data_copy.end(), operation);
    });
    std::cout << "Parallel (std::execution::par): " << par_time << " ms\n";

    data_copy = original_data;
    double par_unseq_time = measure_time([&]() {
        std::for_each(std::execution::par_unseq, data_copy.begin(), data_copy.end(), operation);
    });
    std::cout << "Parallel & Vectorized (std::execution::par_unseq): " << par_unseq_time << " ms\n\n";

    std::cout << "2. Custom Parallel Algorithm \n";
    const unsigned int hardware_threads = std::thread::hardware_concurrency();
    std::cout << "Hardware threads available: " << hardware_threads << "\n\n";

    std::cout << std::left << std::setw(25) << "Number of Threads (K)" << std::setw(20) << "Time (ms)" << "\n";
    std::cout << std::string(45, '-') << "\n";

    double min_time = -1.0;
    unsigned int best_k = 0;

    for (unsigned int k = 1; k <= hardware_threads * 2; ++k) {
        data_copy = original_data;
        double custom_time = measure_time([&]() {
            custom_parallel_for_each(data_copy.begin(), data_copy.end(), operation, k);
        });
        std::cout << std::left << std::setw(25) << k << std::setw(20) << custom_time << "\n";
        if (best_k == 0 || custom_time < min_time) {
            min_time = custom_time;
            best_k = k;
        }
    }

    std::cout << "\nConclusions for Custom Algorithm \n";
    std::cout << "Best performance achieved at K = " << best_k << " threads (" << min_time << " ms).\n";
    if (best_k == hardware_threads) {
        std::cout << "Optimal K matches the number of hardware threads.\n\n";
    } else {
        std::cout << "Optimal K does NOT match the number of hardware threads (" << hardware_threads << ").\n\n";
    }
}
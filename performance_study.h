#pragma once

#include <string>
#include <functional>

void run_performance_study(
    const std::string& operation_name,
    const std::function<void(int&)>& operation,
    size_t data_size
);
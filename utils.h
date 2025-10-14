#pragma once

#include <vector>
#include <functional>

auto measure_time(const std::function<void()>& func) -> double;

auto generate_random_data(size_t size) -> std::vector<int>;
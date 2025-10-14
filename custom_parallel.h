#pragma once

#include <vector>
#include <thread>
#include <iterator>
#include <algorithm>
template<typename Iterator, typename Func>
void custom_parallel_for_each(Iterator begin, Iterator end, Func operation, unsigned int K) {
    const auto total_size = std::distance(begin, end);
    if (K == 0 || total_size == 0) return;

    if (K == 1) {
        std::for_each(begin, end, operation);
        return;
    }

    const auto chunk_size = total_size / K;
    std::vector<std::thread> threads;
    threads.reserve(K);

    auto chunk_begin = begin;
    for (unsigned int i = 0; i < K; ++i) {
        auto chunk_end = chunk_begin;

        if (i == K - 1) {
            chunk_end = end;
        } else {
            std::advance(chunk_end, chunk_size);
        }

        threads.emplace_back([chunk_begin, chunk_end, operation]() {
            std::for_each(chunk_begin, chunk_end, operation);
        });

        chunk_begin = chunk_end;
    }

    for (auto& t : threads) {
        t.join();
    }
}
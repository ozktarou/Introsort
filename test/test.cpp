////////////////////////////////////////////////////////////////////////////////////////////////////
// test.cpp
// Copyright (c) 2025 ozk
// SPDX-License-Identifier: MIT
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <omoteura/intro_sort.h>
#include <random>
#include <string>
#include <vector>

namespace ou = omoteura;

void test(const std::vector<int> &inputItems)
{
    // ou::insertion_sort
    if (inputItems.size() > 100000)
    {
        std::clog << "ou::insertion_sort skipped." << std::endl;
    }
    else
    {
        std::vector<int> items{inputItems};
        std::chrono::steady_clock::time_point start{std::chrono::steady_clock::now()};
        ou::insertion_sort(items.begin(), items.end());
        std::chrono::steady_clock::time_point end{std::chrono::steady_clock::now()};
        if (std::is_sorted(items.begin(), items.end()))
        {
            double seconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
            std::clog << "ou::insertion_sort succeeded. " << std::fixed << seconds << " [s]" << std::endl;
        }
        else
        {
            std::clog << "ou::insertion_sort failed." << std::endl;
        }
    }
    // ou::heap_sort
    {
        std::vector<int> items{inputItems};
        std::chrono::steady_clock::time_point start{std::chrono::steady_clock::now()};
        ou::heap_sort(items.begin(), items.end());
        std::chrono::steady_clock::time_point end{std::chrono::steady_clock::now()};
        if (std::is_sorted(items.begin(), items.end()))
        {
            double seconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
            std::clog << "ou::heap_sort succeeded. " << std::fixed << seconds << " [s]" << std::endl;
        }
        else
        {
            std::clog << "ou::heap_sort failed." << std::endl;
        }
    }
    // ou::quick_sort
    {
        std::vector<int> items{inputItems};
        std::chrono::steady_clock::time_point start{std::chrono::steady_clock::now()};
        ou::quick_sort(items.begin(), items.end());
        std::chrono::steady_clock::time_point end{std::chrono::steady_clock::now()};
        if (std::is_sorted(items.begin(), items.end()))
        {
            double seconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
            std::clog << "ou::quick_sort succeeded. " << std::fixed << seconds << " [s]" << std::endl;
        }
        else
        {
            std::clog << "ou::quick_sort failed." << std::endl;
        }
    }
    // ou::intro_sort
    {
        std::vector<int> items{inputItems};
        std::chrono::steady_clock::time_point start{std::chrono::steady_clock::now()};
        ou::intro_sort(items.begin(), items.end());
        std::chrono::steady_clock::time_point end{std::chrono::steady_clock::now()};
        if (std::is_sorted(items.begin(), items.end()))
        {
            double seconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
            std::clog << "ou::intro_sort succeeded. " << std::fixed << seconds << " [s]" << std::endl;
        }
        else
        {
            std::clog << "ou::intro_sort failed." << std::endl;
        }
    }
    // std::sort
    {
        std::vector<int> items{inputItems};
        std::chrono::steady_clock::time_point start{std::chrono::steady_clock::now()};
        std::sort(items.begin(), items.end());
        std::chrono::steady_clock::time_point end{std::chrono::steady_clock::now()};
        if (std::is_sorted(items.begin(), items.end()))
        {
            double seconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
            std::clog << "std::sort succeeded. " << std::fixed << seconds << " [s]" << std::endl;
        }
        else
        {
            std::clog << "std::sort failed." << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    try
    {
        int n = -1;
        if (argc > 1)
        {
            n = std::stoi(argv[1]);
        }
        if (n < 0)
        {
            std::cerr << "Usage: test <number of items>" << std::endl;
            return 1;
        }

        std::cout << "OMOTEURA_INTROSORT_VERSION_MAJOR = " << OMOTEURA_INTROSORT_VERSION_MAJOR << std::endl;
        std::cout << "OMOTEURA_INTROSORT_VERSION_MINOR = " << OMOTEURA_INTROSORT_VERSION_MINOR << std::endl;
        std::cout << "OMOTEURA_INTROSORT_VERSION_PATCH = " << OMOTEURA_INTROSORT_VERSION_PATCH << std::endl;
        std::cout << "OMOTEURA_INTROSORT_VERSION = " << OMOTEURA_INTROSORT_VERSION << std::endl;

        std::random_device seed_gen{};
        std::mt19937 gen{seed_gen()};

        {
            std::clog << n << " items arranged randomly:" << std::endl;
            std::vector<int> items(n);
            for (int i = 0; i < items.size(); ++i)
            {
                std::uniform_int_distribution<int> dis{0, n - 1};
                int item = dis(gen);
                items[i] = item;
            }
            test(items);
        }
        {
            std::clog << n << " items sorted in ascending order:" << std::endl;
            std::vector<int> items(n);
            int item = 0;
            for (int i = 0; i < items.size(); ++i)
            {
                std::uniform_int_distribution<int> dis{0, 5};
                int step = dis(gen);
                if (item > std::numeric_limits<int>::max() - step)
                {
                    throw std::out_of_range("item overflowed");
                }
                item += step;
                items[i] = item;
            }
            test(items);
        }
        {
            std::clog << n << " items sorted in descending order:" << std::endl;
            std::vector<int> items(n);
            int item = 0;
            for (int i = items.size() - 1; i >= 0; --i)
            {
                std::uniform_int_distribution<int> dis{0, 5};
                int step = dis(gen);
                if (item > std::numeric_limits<int>::max() - step)
                {
                    throw std::out_of_range("item overflowed");
                }
                item += step;
                items[i] = item;
            }
            test(items);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

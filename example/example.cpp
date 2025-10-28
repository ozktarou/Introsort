////////////////////////////////////////////////////////////////////////////////////////////////////
// example.cpp
// Copyright (c) 2025 ozk
// SPDX-License-Identifier: MIT
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <omoteura/intro_sort.h>
#include <vector>

namespace ou = omoteura;

int main(int argc, char *argv[])
{
    std::vector<int> items{2, 5, 3, 8, 5};

    std::cout << "input: [";
    for (int item : items)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    ou::intro_sort(items.begin(), items.end());

    std::cout << "sorted (asc) ou::intro_sort: [";
    for (int item : items)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    ou::intro_sort(items.begin(), items.end(), std::greater<int>{});

    std::cout << "sorted (desc) ou::intro_sort: [";
    for (int item : items)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    ou::insertion_sort(items.begin(), items.end());

    std::cout << "sorted (asc) ou::insertion_sort: [";
    for (int item : items)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    ou::insertion_sort(items.begin(), items.end(), std::greater<int>{});

    std::cout << "sorted (desc) ou::insertion_sort: [";
    for (int item : items)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    ou::heap_sort(items.begin(), items.end());

    std::cout << "sorted (asc) ou::heap_sort: [";
    for (int item : items)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    ou::heap_sort(items.begin(), items.end(), std::greater<int>{});

    std::cout << "sorted (desc) ou::heap_sort: [";
    for (int item : items)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    ou::quick_sort(items.begin(), items.end());

    std::cout << "sorted (asc) ou::quick_sort: [";
    for (int item : items)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    ou::quick_sort(items.begin(), items.end(), std::greater<int>{});

    std::cout << "sorted (desc) ou::quick_sort: [";
    for (int item : items)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    return 0;
}

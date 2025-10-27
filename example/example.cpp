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
    std::vector<int> input{2, 5, 3, 8, 5};

    std::cout << "input: [";
    for (int item : input)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    std::vector<int> sorted_asc{input};
    ou::intro_sort(sorted_asc.begin(), sorted_asc.end());

    std::cout << "sorted (asc): [";
    for (int item : sorted_asc)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    std::vector<int> sorted_desc{input};
    ou::intro_sort(sorted_desc.begin(), sorted_desc.end(), std::greater<int>{});

    std::cout << "sorted (desc): [";
    for (int item : sorted_desc)
    {
        std::cout << " " << item;
    }
    std::cout << " ]" << std::endl;

    return 0;
}

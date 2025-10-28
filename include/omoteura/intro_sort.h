////////////////////////////////////////////////////////////////////////////////////////////////////
// intro_sort.h
// Copyright (c) 2025 ozk
// SPDX-License-Identifier: MIT
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iterator>
#include <utility>

#define OMOTEURA_INTROSORT_VERSION_MAJOR 1
#define OMOTEURA_INTROSORT_VERSION_MINOR 0
#define OMOTEURA_INTROSORT_VERSION_PATCH 0

#define OMOTEURA_INTROSORT_TO_VERSION(major, minor, patch) (major * 10000 + minor * 100 + patch)
#define OMOTEURA_INTROSORT_VERSION        \
    OMOTEURA_INTROSORT_TO_VERSION(        \
        OMOTEURA_INTROSORT_VERSION_MAJOR, \
        OMOTEURA_INTROSORT_VERSION_MINOR, \
        OMOTEURA_INTROSORT_VERSION_PATCH)

namespace omoteura
{
    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    // insertion_sort<RandomAccessIterator>
    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    template <typename RandomAccessIterator>
    void insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
    {
        using T = typename std::iterator_traits<RandomAccessIterator>::value_type;
        insertion_sort(first, last, std::less<T>{});
    }

    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    // insertion_sort<RandomAccessIterator, Compare>
    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    template <typename RandomAccessIterator, typename Compare>
    void insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        using T = typename std::iterator_traits<RandomAccessIterator>::value_type;
        if (first < last)
        {
            for (RandomAccessIterator i{first + 1}; i != last; ++i)
            {
                if (comp(*i, *(i - 1)))
                {
                    T value{std::move(*i)};
                    RandomAccessIterator j{i - 1};
                    RandomAccessIterator current{i};
                    try
                    {
                        do
                        {
                            *current = std::move(*j);
                            current = j;
                            if (j == first)
                            {
                                break;
                            }
                            --j;
                        } while (comp(value, *j));

                        *current = std::move(value);
                    }
                    catch (...)
                    {
                        *current = std::move(value);
                        throw;
                    }
                }
            }
        }
    }

    namespace detail
    {
        //---------+---------+---------+---------+---------+---------+---------+---------+---------+
        // make_heap<RandomAccessIterator, Compare>
        //---------+---------+---------+---------+---------+---------+---------+---------+---------+
        template <typename RandomAccessIterator, typename Compare>
        void make_heap(RandomAccessIterator first,
                       typename std::iterator_traits<RandomAccessIterator>::difference_type n,
                       Compare comp)
        {
            using Diff = typename std::iterator_traits<RandomAccessIterator>::difference_type;
            assert(n >= 2);
            for (Diff i{n / 2}; i > 0; --i)
            {
                down_heap(first, n, i - 1, comp);
            }
        }

        //---------+---------+---------+---------+---------+---------+---------+---------+---------+
        // down_heap<RandomAccessIterator, Compare>
        //---------+---------+---------+---------+---------+---------+---------+---------+---------+
        template <typename RandomAccessIterator, typename Compare>
        void down_heap(RandomAccessIterator first,
                       typename std::iterator_traits<RandomAccessIterator>::difference_type n,
                       typename std::iterator_traits<RandomAccessIterator>::difference_type i,
                       Compare comp)
        {
            using T = typename std::iterator_traits<RandomAccessIterator>::value_type;
            using Diff = typename std::iterator_traits<RandomAccessIterator>::difference_type;
            assert(0 <= i && i < n);
            T value{std::move(first[i])};
            try
            {
                while (2 * i + 1 < n)
                {
                    Diff child{2 * i + 1};
                    if (child + 1 < n && !comp(first[child + 1], first[child]))
                    {
                        ++child;
                    }
                    if (comp(value, first[child]))
                    {
                        first[i] = std::move(first[child]);
                        i = child;
                    }
                    else
                    {
                        break;
                    }
                }
                first[i] = std::move(value);
            }
            catch (...)
            {
                first[i] = std::move(value);
                throw;
            }
        }
    } // namespace detail

    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    // heap_sort<RandomAccessIterator>
    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    template <typename RandomAccessIterator>
    void heap_sort(RandomAccessIterator first, RandomAccessIterator last)
    {
        using T = typename std::iterator_traits<RandomAccessIterator>::value_type;
        heap_sort(first, last, std::less<T>{});
    }

    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    // heap_sort<RandomAccessIterator, Compare>
    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    template <typename RandomAccessIterator, typename Compare>
    void heap_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        using std::swap;
        using Diff = typename std::iterator_traits<RandomAccessIterator>::difference_type;
        Diff n{last - first};
        if (n >= 2)
        {
            detail::make_heap(first, n, comp);
            do
            {
                --n;
                swap(first[0], first[n]);
                detail::down_heap(first, n, 0, comp);
            } while (n > 1);
        }
    }

    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    // quick_sort<RandomAccessIterator>
    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    template <typename RandomAccessIterator>
    void quick_sort(RandomAccessIterator first, RandomAccessIterator last)
    {
        using T = typename std::iterator_traits<RandomAccessIterator>::value_type;
        quick_sort(first, last, std::less<T>{});
    }

    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    // quick_sort<RandomAccessIterator, Compare>
    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    template <typename RandomAccessIterator, typename Compare>
    void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        using Diff = typename std::iterator_traits<RandomAccessIterator>::difference_type;
        using std::swap;
        constexpr int threshold = 16;
        Diff n{last - first};
        if (n <= threshold)
        {
            insertion_sort(first, last, comp);
        }
        else
        {
            RandomAccessIterator l{first};
            RandomAccessIterator r{last - 1};
            RandomAccessIterator m{first + (n / 2)};
            if (comp(*m, *l))
            {
                swap(*l, *m);
            }
            if (comp(*r, *l))
            {
                swap(*l, *r);
            }
            if (comp(*m, *r))
            {
                swap(*m, *r);
            }
            // r is pivot
            RandomAccessIterator i{l};
            RandomAccessIterator j{r - 1};
            while (true)
            {
                while (i <= j && comp(*i, *r))
                {
                    ++i;
                }
                while (j >= i && comp(*r, *j))
                {
                    --j;
                }
                if (i >= j)
                {
                    break;
                }
                swap(*i, *j);
                ++i;
                --j;
            }
            swap(*i, *r);
            quick_sort(first, i, comp);
            quick_sort(i + 1, last, comp);
        }
    }

    namespace detail
    {
        //---------+---------+---------+---------+---------+---------+---------+---------+---------+
        // intro_sort_impl<RandomAccessIterator, Compare>
        //---------+---------+---------+---------+---------+---------+---------+---------+---------+
        template <typename RandomAccessIterator, typename Compare>
        void intro_sort_impl(RandomAccessIterator first,
                             RandomAccessIterator last,
                             Compare comp,
                             int depthLimit)
        {
            using Diff = typename std::iterator_traits<RandomAccessIterator>::difference_type;
            using std::swap;
            constexpr int threshold = 16;
            Diff n{last - first};
            if (n <= threshold)
            {
                insertion_sort(first, last, comp);
            }
            else
            {
                if (depthLimit <= 0)
                {
                    heap_sort(first, last, comp);
                }
                else
                {
                    RandomAccessIterator l{first};
                    RandomAccessIterator r{last - 1};
                    RandomAccessIterator m{first + (n / 2)};
                    if (comp(*m, *l))
                    {
                        swap(*l, *m);
                    }
                    if (comp(*r, *l))
                    {
                        swap(*l, *r);
                    }
                    if (comp(*m, *r))
                    {
                        swap(*m, *r);
                    }
                    // r is pivot
                    RandomAccessIterator i{l};
                    RandomAccessIterator j{r - 1};
                    while (true)
                    {
                        while (i <= j && comp(*i, *r))
                        {
                            ++i;
                        }
                        while (j >= i && comp(*r, *j))
                        {
                            --j;
                        }
                        if (i >= j)
                        {
                            break;
                        }
                        swap(*i, *j);
                        ++i;
                        --j;
                    }
                    swap(*i, *r);
                    intro_sort_impl(first, i, comp, depthLimit - 1);
                    intro_sort_impl(i + 1, last, comp, depthLimit - 1);
                }
            }
        }
    } // namespace detail

    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    // intro_sort<RandomAccessIterator>
    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    template <typename RandomAccessIterator>
    void intro_sort(RandomAccessIterator first, RandomAccessIterator last)
    {
        using T = typename std::iterator_traits<RandomAccessIterator>::value_type;
        intro_sort(first, last, std::less<T>{});
    }

    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    // intro_sort<RandomAccessIterator, Compare>
    //---+---------+---------+---------+---------+---------+---------+---------+---------+---------+
    template <typename RandomAccessIterator, typename Compare>
    void intro_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        int depthLimit = 2 * static_cast<int>(std::log2(
                                 std::max(1.0, static_cast<double>(last - first))));
        detail::intro_sort_impl(first, last, comp, depthLimit);
    }
} // namespace omoteura

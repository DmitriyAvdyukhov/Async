#pragma once
#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>
#include <future>
#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <string>

using namespace std;

template <typename RandomAccessIterator, typename Value>
RandomAccessIterator LowerBound(const execution::sequenced_policy&, RandomAccessIterator range_begin, RandomAccessIterator range_end, const Value& value)
{
    auto left_bound = range_begin;
    auto right_bound = range_end;
    while (left_bound + 1 < right_bound)
    {
        const auto middle = left_bound + (right_bound - left_bound) / 2;
        if (*middle < value)
        {
            left_bound = middle;
        }
        else
        {
            right_bound = middle;
        }
    }
    if (left_bound == range_begin && !(*left_bound < value))
    {
        return left_bound;
    }
    else
    {
        return right_bound;
    }
}

template <typename RandomAccessIterator, typename Value>
RandomAccessIterator LowerBound(const execution::parallel_policy&, RandomAccessIterator range_begin, RandomAccessIterator range_end, const Value& value)
{
    auto left_bound = range_begin;
    auto right_bound = range_end;
    while (left_bound + 1 < right_bound)
    {
        if ((right_bound - left_bound) / 3 > 0)
        {
            const auto middle_left = left_bound + (right_bound - left_bound) / 3;
            const auto middle_rigth = left_bound + ((right_bound - left_bound) / 3) * 2;
            future<bool>left = async([&middle_left, &value]
                {
                    return (*middle_left < value);
                });

            future<bool>centr = async([&middle_rigth, &value]
                {
                    return (*middle_rigth < value);
                });
            if (!left.get())
            {
                right_bound = middle_left;
            }
            else if (!centr.get())
            {
                left_bound = middle_left;
                right_bound = middle_rigth;
            }
            else
            {
                left_bound = middle_rigth;
            }
        }
        else
        {
            const auto middle = left_bound + (right_bound - left_bound) / 2;
            if (*middle < value)
            {
                left_bound = middle;
            }
            else
            {
                right_bound = middle;
            }
        }
    }

    if (left_bound == range_begin && !(*left_bound < value))
    {
        return left_bound;
    }
    else
    {
        return right_bound;
    }
}

template <typename RandomAccessIterator, typename Value>
RandomAccessIterator LowerBound(RandomAccessIterator range_begin, RandomAccessIterator range_end, const Value& value)
{
    return LowerBound(execution::seq, range_begin, range_end, value);
}
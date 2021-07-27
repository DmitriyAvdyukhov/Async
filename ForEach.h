#pragma once
#include <algorithm>
#include <execution>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <thread>
#include <future>
#include <iterator>

using namespace std;




template <typename ForwardRange, typename Function>
void ForEach(ForwardRange& range, Function function) 
{
    for_each(range.begin(), range.end(), function);
}

template <typename ForwardRange, typename Function, class ExecutionPolicy>
void ForEach(const ExecutionPolicy& policy, ForwardRange& range, Function function)
{
    using category = typename iterator_traits<typename ForwardRange::iterator>::iterator_category;
    if constexpr (is_same_v<ExecutionPolicy, execution::sequenced_policy> 
        || is_same_v<category, random_access_iterator_tag>)
    {
        for_each(policy, range.begin(), range.end(), function);
    }
    
    else
    {
        static constexpr int PART_COUNT = 4;
        const auto part_length = range.size() / PART_COUNT;
        auto part_begin = range.begin();
        auto part_end = next(part_begin, part_length);
        
        vector<future<void>> futures;
        for (int i = 0; i < PART_COUNT; ++i, part_begin = part_end,
            part_end = (i >= PART_COUNT - 1 ? range.end() : next(part_begin, part_length)))
        {
            futures.push_back(async([function, part_begin, part_end]
                {
                    for_each(part_begin, part_end, function); 
                }));
        }
    }    
}

template <typename ForwardRange, typename Function, class ExecutionPolicy>
void ForEach1(const ExecutionPolicy&, ForwardRange& range, Function function)
{
    using category = typename iterator_traits<typename ForwardRange::iterator>::iterator_category;
    if constexpr (is_same_v<ExecutionPolicy, execution::parallel_policy>)
    {
        if constexpr (!is_same_v<category, random_access_iterator_tag>)
        {
            static constexpr int PART_COUNT = 4;
            const auto part_length = range.size() / PART_COUNT;
            auto part_begin = range.begin();
            auto part_end = next(part_begin, part_length);

            vector<future<void>> futures;
            for (int i = 0; i < PART_COUNT; ++i, part_begin = part_end,
                part_end = (i >= PART_COUNT - 1 ? range.end() : next(part_begin, part_length)))
            {
                futures.push_back(async([function, part_begin, part_end]
                    { for_each(part_begin, part_end, function); }));
            }
        }
        else
        {
            for_each(execution::par, range.begin(), range.end(), function);
        }
    }
    else
    {
        for_each(range.begin(), range.end(), function);
    }
}
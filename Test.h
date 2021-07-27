#pragma once
#include <algorithm>
#include <list>
#include <random>
#include <string>
#include <string_view>
#include <type_traits>

#include "log_duration.h"

using namespace std;

string GenerateWord(mt19937& generator, int max_length) 
{
    const int length = uniform_int_distribution(1, max_length)(generator);
    string word;
    word.reserve(length);
    for (int i = 0; i < length; ++i) 
    {
        word.push_back(uniform_int_distribution('a', 'z')(generator));
    }
    return word;
}

template <template<typename> typename Container>
Container<string> GenerateDictionary(mt19937& generator, int word_count, int max_length)
{
    vector<string> words;
    words.reserve(word_count);
    for (int i = 0; i < word_count; ++i)
    {
        words.push_back(GenerateWord(generator, max_length));
    }
    return Container(words.begin(), words.end());
}


//struct Reverser 
//{
//    void operator()(auto& value) const 
//    {
//        reverse(value.begin(), value.end());
//    }
//};
//
//void Test(string_view mark, auto keys, auto function)
//{
//    LOG_DURATION(mark);
//    function(keys, Reverser{});
//}

#define TEST(function) Test(#function, keys, function<remove_const_t<decltype(keys)>, Reverser>)

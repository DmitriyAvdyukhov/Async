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

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats& other)
    {
        for (const auto [word, frequency] : other.word_frequences)
        {
            word_frequences[word] += frequency;
        }
    }
};

std::vector<std::string_view> SplitIntoWords(std::string_view str)
{
    std::vector<std::string_view> result;
    while (true)
    {
        const auto space = str.find(' ');
        if (space != 0 && !str.empty())
        {
            result.push_back(str.substr(0, space));
        }
        if (space == str.npos) {
            break;
        }
        else {
            str.remove_prefix(space + 1);
        }
    }

    return result;
}
using KeyWords = set<string, less<>>;

Stats ExploreKeyWords(const KeyWords& key_words, istream& input)
{
    Stats stats{ };
    string words;
    vector<string> strings;
    while (getline(input, words))
    {
        strings.push_back(words);
    }


    vector<future<void>>stats_;

    for (const auto& temp : strings)
    {
        stats_.push_back(async([temp, key_words, &stats]
            {
                for (auto word : SplitIntoWords(temp))
                {
                    if (key_words.find(word) != key_words.end())
                    {
                        string temp{ word };
                        stats.word_frequences[temp]++;
                    }
                }
            }));

    }

    return stats;
}

Stats ExploreKeyWords1(const KeyWords& key_words, istream& input)
{
    Stats stats{ };
    string words;
    vector<string> strings;
    while (getline(input, words))
    {
        strings.push_back(words);
    }

    for (const auto& word : key_words)
    {
        stats.word_frequences[word] = 0;
    }

    for (const auto& temp : strings)
    {
        for (const auto& word : SplitIntoWords(temp))
        {
            if (key_words.find(word) != key_words.end())
            {
                string temp{ word };
                stats.word_frequences[temp]++;
            }
        }
    }
    return stats;
}
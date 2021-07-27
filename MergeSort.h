#pragma once
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <future>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

// �������� � ������� ��������������
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // 1. ���� �������� �������� ������ 2 ���������, ������� �� �������
    int range_length = range_end - range_begin;
    if (range_length < 2) {
        return;
    }

    // 2. ������ ������, ���������� ��� �������� �������� ���������
    vector elements(range_begin, range_end);
    // ��� ��������� � typename iterator_traits<RandomIt>::value_type

    // 3. ��������� ������ �� ��� ������ �����
    auto mid = elements.begin() + range_length / 2;

    // 4. �������� ������� MergeSort �� ������ �������� �������
    auto left_future = async([&]
        {
            MergeSort(elements.begin(), mid);
        });

    auto rigth_future = async([&]
        {
            MergeSort(mid, elements.end());
        });
    left_future.get();
    rigth_future.get();
   
    // 5. � ������� ��������� merge ������� ��������������� ��������
    // � �������� ��������
    // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
    merge(elements.begin(), mid, mid, elements.end(), range_begin);
}
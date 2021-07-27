#include "Stats.h"
#include "MergeSort.h"
#include "LowerBaund.h"
#include "log_duration.h"
#include "ForEach.h"
//#include "Test.h"





template <typename Strings>
void PrintStrings(const Strings& strings) {
    for (string_view s : strings) {
        cout << s << " ";
    }
    cout << endl;
}


int main() {
    //const vector<string> strings = 
    //{
    //    "cat",
    //    "dog",
    //    "dog",
    //    "horse"
    //};
    //const vector<string> requests = 
    //{
    //    "bear",
    //    "cat",
    //    "deer",
    //    "dog",
    //    "dogs",
    //    "horses"
    //};
    //// последовательные версии
    //cout << "Request [" << requests[0] << "] → position "
    //    << LowerBound(strings.begin(), strings.end(), requests[0]) - strings.begin() << endl;
    //cout << "Request [" << requests[1] << "] → position "
    //    << LowerBound(execution::seq, strings.begin(), strings.end(), requests[1]) - strings.begin() << endl;
    //cout << "Request [" << requests[2] << "] → position "
    //    << LowerBound(execution::seq, strings.begin(), strings.end(), requests[2]) - strings.begin() << endl;   
    //cout << "Request [" << requests[3] << "] → position "
    //    << LowerBound(strings.begin(), strings.end(), requests[3]) - strings.begin() << endl;
    //cout << "Request [" << requests[4] << "] → position "
    //    << LowerBound(execution::seq, strings.begin(), strings.end(), requests[4]) - strings.begin() << endl;
    //cout << "Request [" << requests[5] << "] → position "
    //    << LowerBound(execution::seq, strings.begin(), strings.end(), requests[5]) - strings.begin() << endl;
    //cout << endl;   
    //// параллельные
    //cout << "Request [" << requests[0] << "] → position "
    //    << LowerBound(execution::par, strings.begin(), strings.end(), requests[0]) - strings.begin() << endl;
    //cout << "Request [" << requests[1] << "] → position "
    //    << LowerBound(execution::par, strings.begin(), strings.end(), requests[1]) - strings.begin() << endl;
    //cout << "Request [" << requests[2] << "] → position "
    //    << LowerBound(execution::par, strings.begin(), strings.end(), requests[2]) - strings.begin() << endl;
    //cout << "Request [" << requests[3] << "] → position "
    //    << LowerBound(execution::par, strings.begin(), strings.end(), requests[3]) - strings.begin() << endl;
    //cout << "Request [" << requests[4] << "] → position "
    //    << LowerBound(execution::par, strings.begin(), strings.end(), requests[4]) - strings.begin() << endl;
    //cout << "Request [" << requests[5] << "] → position "
    //    << LowerBound(execution::par, strings.begin(), strings.end(), requests[5]) - strings.begin() << endl;
    //
    //const KeyWords key_words = { "yangle", "rocks", "sucks", "all" };
    //stringstream ss;
    //ss << "this new yangle service really rocks\n";
    //ss << "It sucks when yangle isn't available\n";
    //ss << "10 reasons why yangle is the best IT company\n";
    //ss << "yangle rocks others suck\n";
    //ss << "Goondex really sucks, but yangle  rocks. Use yangle\n";
    //Stats result = ExploreKeyWords(key_words, ss);
    //for (const auto& [word, frequency] : result.word_frequences) {
    //    cout << word << " " << frequency << endl;
    //}
    //
    //ss << "this new yangle service really rocks\n";
    //ss << "It sucks when yangle isn't available\n";
    //ss << "10 reasons why yangle is the best IT company\n";
    //ss << "yangle rocks others suck\n";
    //ss << "Goondex really sucks, but yangle  rocks. Use yangle\n";
    //Stats result1 = ExploreKeyWords1(key_words, ss);
    //for (const auto& [word, frequency] : result1.word_frequences) {
    //    cout << word << " " << frequency << " \n";
    //}
    //
    //
    //result += result1;
    //for (const auto& [word, frequency] : result.word_frequences) {
    //    cout << word << " " << frequency << endl;
    //}
    //mt19937 generator;
    //vector<int> test_vector(10);
    //// iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    //// Заполняет диапазон последовательно возрастающими значениями
    //iota(test_vector.begin(), test_vector.end(), 1);
    //// shuffle   -> https://ru.cppreference.com/w/cpp/algorithm/random_shuffle
    //// Перемешивает элементы в случайном порядке
    //shuffle(test_vector.begin(), test_vector.end(), generator);
    //// Выводим вектор до сортировки
    //PrintRange(test_vector.begin(), test_vector.end());
    //// Сортируем вектор с помощью сортировки слиянием
    //MergeSort(test_vector.begin(), test_vector.end());
    //// Выводим результат
    //PrintRange(test_vector.begin(), test_vector.end());
    //// Проверяем, можно ли передать указатели
    //MergeSort(test_vector.data(), test_vector.data() + test_vector.size());

    auto reverser = [](string& s) { reverse(s.begin(), s.end()); };

    list<string> strings_list = { "cat", "dog", "code" };

    ForEach(strings_list, reverser);
    PrintStrings(strings_list);
    // tac god edoc

    ForEach(execution::seq, strings_list, reverser);
    PrintStrings(strings_list);
    // cat dog code

    // единственный из вызовов, где должна работать ваша версия
    // из предыдущего задания
    ForEach(execution::par, strings_list, reverser);
    PrintStrings(strings_list);
    // tac god edoc

    vector<string> strings_vector = { "cat", "dog", "code" };

    ForEach(strings_vector, reverser);
    PrintStrings(strings_vector);
    // tac god edoc

    ForEach(execution::seq, strings_vector, reverser);
    PrintStrings(strings_vector);
    // cat dog code

    ForEach(execution::par, strings_vector, reverser);
    PrintStrings(strings_vector);
    return 0;
}
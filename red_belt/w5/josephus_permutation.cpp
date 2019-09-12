#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <deque>
#include <list>

using namespace std;


//ostream& operator<<(ostream& os, const list<size_t> &l){
//    os << "LIST " << endl;
//    for(const auto &el: l)
//        os << el << ' ';
//    os << endl;
//    return os;
//}
//
//
//ostream& operator<<(ostream& os, const vector<size_t> &l){
//    os << "INDEXES " << endl;
//    for(const auto &el: l)
//        os << el << ' ';
//    os << endl;
//    return os;
//}

template <typename RandomIt>
void ReplaceAccordingToIndex(const vector<size_t> &want_index, RandomIt& first, RandomIt& last){

    size_t n_els = distance(first, last);
    map<size_t , size_t > original_index_to_current_pose;
    for(size_t i = 0; i < n_els; ++i){
        original_index_to_current_pose[i] = i;
    }  // filling actual place tracker
    map<size_t , size_t > current_pose_to_original_index = original_index_to_current_pose; // the same initially

    auto it = first;
    for(size_t pos = 0; pos < n_els; ++pos, ++it){
        size_t desired_elem =  want_index[pos];
        size_t now_elem_at_this_position = current_pose_to_original_index[pos];
        if (now_elem_at_this_position == desired_elem)
            continue;
        size_t desired_elem_position = original_index_to_current_pose[desired_elem];
        auto desired_elem_it = first + desired_elem_position;
        iter_swap(desired_elem_it, it);
        // now our current element is at other position and we will need it once more
        current_pose_to_original_index[desired_elem_position] = now_elem_at_this_position; // after replacement
        original_index_to_current_pose[now_elem_at_this_position] = desired_elem_position; // after replacement
    }
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {

    size_t n_elements = distance(first, last);
    vector<size_t> index_order(n_elements);
    list<size_t > available_elements(n_elements);
    iota(available_elements.begin(), available_elements.end(), 0);
//    cout << available_elements << endl;

    auto live_els_it = available_elements.begin();
    size_t  i = 0;

    for(; i < n_elements && n_elements - i >= step_size; ++i){
//        cout << "I [" << i << "]" << endl;
        index_order[i] = (*live_els_it);  // remember for the answer
//        cout << index_order << endl;

        live_els_it = available_elements.erase(live_els_it);
//        cout << available_elements << endl;

        size_t make_steps = step_size - 1;
        while(make_steps) {
            if (live_els_it == available_elements.end()) {
                live_els_it = available_elements.begin();
            }
            ++live_els_it;
            --make_steps;
        }
    }

    while (!available_elements.empty()){
        if(live_els_it == available_elements.end())
            live_els_it = available_elements.begin();
        index_order[i++] = (*live_els_it);
        live_els_it = available_elements.erase(live_els_it);
        ++live_els_it;
    }

    ReplaceAccordingToIndex(index_order, first, last);
}

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

void TestIntVector() {
  const vector<int> numbers = MakeTestVector();
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
    ASSERT_EQUAL(numbers_copy, numbers);
  }
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
    ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
  }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
  int value;

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
  return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
  return os << v.value;
}

void TestAvoidsCopying() {
  vector<NoncopyableInt> numbers;
  numbers.push_back({1});
  numbers.push_back({2});
  numbers.push_back({3});
  numbers.push_back({4});
  numbers.push_back({5});

  MakeJosephusPermutation(begin(numbers), end(numbers), 2);

  vector<NoncopyableInt> expected;
  expected.push_back({1});
  expected.push_back({3});
  expected.push_back({5});
  expected.push_back({4});
  expected.push_back({2});

  ASSERT_EQUAL(numbers, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestAvoidsCopying);
  return 0;
}

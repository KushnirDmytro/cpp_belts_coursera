#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <deque>
#include <list>

using namespace std;


template <typename T>
ostream& operator<<(ostream& os, const list<T> &l){
    os << "LIST " << endl;
    for(const auto &el: l)
        os << el << ' ';
    os << endl;
    return os;
}


template <typename RandomIt>
void print_range(RandomIt begin, RandomIt end){
    cout << "Range" << endl;
    for(auto i = begin; i < end; ++i)
        cout << *i << ' ';
    cout << endl;
}
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

template<typename T>
void EraseAndAdvance(typename list<T> ::iterator &it, list<T> &l, size_t steps){
    const auto it_next = next(it);
    l.erase(it);
    it = it_next;
    if(it == l.end())
        it = l.begin();
    for(size_t i = steps; steps <= l.size() && i > 0; --i){
        ++it;
        if(it == l.end())
            it = l.begin();
    }
}

template <typename RandomIt>
void MakeJosephusPermutationInplace(RandomIt first, RandomIt last, size_t step_size) {
    size_t n_elements = distance(first, last);
    vector<size_t> index_order(n_elements);
    list<size_t > available_elements(n_elements);
    iota(available_elements.begin(), available_elements.end(), 0);

    auto live_els_it = available_elements.begin();
    size_t  i = 0;

    for(; i < n_elements && n_elements - i >= step_size; ++i){
        index_order[i] = (*live_els_it);  // remember for the answer
        live_els_it = available_elements.erase(live_els_it);
        EraseAndAdvance<size_t>(live_els_it, available_elements, step_size - 1);
    }

    //  place indexes of the rest of elements to the desired index
    while ( i < n_elements){
        index_order[i++] = (*live_els_it);
        if (live_els_it == available_elements.end()){
            live_els_it = available_elements.begin();
        }
        live_els_it = available_elements.erase(live_els_it);
    }

    ReplaceAccordingToIndex(index_order, first, last);
}


template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, size_t step_size) {
    using list_t = list<typename RandomIt::value_type>;
    list_t l;
    for (auto i = first; i < last; ++i){
        l.push_back(move(*i));
    }

    auto result_placing_it = first;
    auto list_it = l.begin();
    size_t el_count = distance(first, last);

    for( ; el_count > 0;
           EraseAndAdvance(list_it, l, step_size - 1),
                   ++result_placing_it,
                   --el_count ){

//        print_range(first, last);
//        cout << l << endl;
//        cout << "Moving "<<*list_it << endl;
        *result_placing_it = move(*list_it);
    }


}




//template <typename Container, typename ForwardIt>
//ForwardIt LoopIterator(Container& container, ForwardIt pos) {
//    return pos == container.end() ? container.begin() : pos;
//}
//
//template <typename RandomIt>
//void MakeJosephusPermutation(RandomIt first, RandomIt last,
//                             uint32_t step_size) {
//    list<typename RandomIt::value_type> pool;
//    for (auto it = first; it != last; ++it) {
//        pool.push_back(move(*it));
//    }
//
//    auto cur_pos = pool.begin();
//    while (!pool.empty()) {
//        *(first++) = move(*cur_pos);
//        if (pool.size() == 1) {
//            break;
//        }
//        const auto next_pos = LoopIterator(pool, next(cur_pos));
//        pool.erase(cur_pos);
//        cur_pos = next_pos;
//        for (uint32_t step_index = 1; step_index < step_size; ++step_index) {
//            cur_pos = LoopIterator(pool, next(cur_pos));
//        }
//    }
//}



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

void TestSmallVector(){
    {
        vector<int> numbers_copy = {};
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, vector<int>{});
    }

    {
        vector<int> numbers_copy = {};
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>{});
    }

    {
        vector<int> numbers_copy = {1};
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, vector<int>{1});
    }
    {
        vector<int> input = {1, 2};
        vector<int> rez = {1, 2};
        MakeJosephusPermutation(begin(input), end(input), 2);
        ASSERT_EQUAL( input, rez );
    }
}


void TestStringVec() {
    {
        vector<string> numbers_copy = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<string>({"0", "3", "6", "9", "4", "8", "5", "2", "7", "1"}));
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
    RUN_TEST(tr, TestStringVec);
    RUN_TEST(tr, TestSmallVector);
    return 0;
}

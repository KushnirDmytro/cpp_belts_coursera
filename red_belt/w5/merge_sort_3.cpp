#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // Напишите реализацию функции,
  // не копируя сортируемые элементы
    if (distance(range_begin, range_end) < 3) {
        return;
    }

    vector<typename RandomIt::value_type> local_buf(make_move_iterator(range_begin), make_move_iterator(range_end));
    size_t offset = local_buf.size() / 3;

    auto border_1_2 = next(local_buf.begin(), offset);
    auto border_2_3 = next(border_1_2, offset);

    MergeSort(local_buf.begin(), border_1_2);
    MergeSort(border_1_2, border_2_3);
    MergeSort(border_2_3, local_buf.end());

    vector<typename RandomIt::value_type> temp;

    merge(
            make_move_iterator(local_buf.begin()),
            make_move_iterator(border_1_2),
            make_move_iterator(border_1_2),
            make_move_iterator(border_2_3),
            back_inserter(temp)
        );

    merge(
            make_move_iterator(temp.begin()),
            make_move_iterator(temp.end()),
            make_move_iterator(border_2_3),
            make_move_iterator(local_buf.end()),
            range_begin
        );
}



void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}

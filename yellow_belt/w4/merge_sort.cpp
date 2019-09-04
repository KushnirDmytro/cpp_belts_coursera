//
// Created by dkushn on 14.08.19.
//

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
//template <typename RandomIt>
//void MergeSort(RandomIt range_begin, RandomIt range_end){
//    if (distance(range_begin, range_end) < 2) {
//        return;
//    }
//    vector<typename RandomIt::value_type> local_buf(range_begin, range_end);
//    auto middle_vector_it = local_buf.begin() + local_buf.size() / 2;
//    MergeSort(local_buf.begin(), middle_vector_it);
//    MergeSort(middle_vector_it, local_buf.end());
//    merge(local_buf.begin(), middle_vector_it, middle_vector_it,  local_buf.end(), range_begin);
//}

void MergeSort(RandomIt range_begin, RandomIt range_end){
    if (distance(range_begin, range_end) < 3) {
        return;
    }

    vector<typename RandomIt::value_type> local_buf(range_begin, range_end);
    size_t offset = local_buf.size() / 3;
    auto border_1_2 {local_buf.begin()};
    advance(border_1_2, offset);
    auto border_2_3 {border_1_2};
    advance(border_2_3, offset);
    MergeSort(local_buf.begin(), border_1_2);
    MergeSort(border_1_2, border_2_3);
    MergeSort(border_2_3, local_buf.end());
    vector<typename RandomIt::value_type> temp;
    merge(local_buf.begin(), border_1_2, border_1_2,  border_2_3, back_inserter(temp));
    merge(temp.begin(), temp.end(), border_2_3,  local_buf.end(), range_begin);
}


int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

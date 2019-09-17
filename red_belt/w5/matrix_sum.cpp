#include "test_runner.h"
#include <vector>
#include <future>
#include <algorithm>
#include <numeric>
using namespace std;


int64_t SumVectors( vector<vector<int>>::const_iterator begin,  vector<vector<int>>::const_iterator end){
    int64_t res{0};
    for ( auto &vec_it = begin; vec_it != end; advance(vec_it, 1)){
        for (const auto& el: *vec_it){
            res += el;
        }
    }
    return res;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    size_t N_threads = 6;
    size_t partition_size = matrix.size() / N_threads;
    vector<future<int64_t>>vec_res;
    auto it = matrix.begin();
    for(size_t n_thread{0}; n_thread < N_threads; ++n_thread, it += partition_size){
        vec_res.push_back(async ([it, partition_size, N_threads, n_thread, &matrix]{ return SumVectors(it, n_thread == N_threads - 1 ? matrix.end(): it + partition_size); }));
    }
    int64_t  total_sum{0};
    for (auto &call : vec_res)
        total_sum += call.get();
    return total_sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}

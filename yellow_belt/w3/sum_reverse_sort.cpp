//
// Created by dkushn on 13.08.19.
//

#pragma once

#include "sum_reverse_sort.h"

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int Sum(int x, int y){
    return x + y;
};

string Reverse(string s){
    reverse(s.begin(), s.end());
    return s;
};

void Sort(vector<int>& nums){
    sort(nums.begin(), nums.end());
}

//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


//Реализуйте функцию vector<int> Reversed(const vector<int>& v), возвращающую копию вектора v, в которой числа переставлены в обратном порядке.

/*
 *vector<int> numbers = {1, 5, 3, 4, 2};
Reverse(numbers);
// numbers должен оказаться равен {2, 4, 3, 5, 1}
 */


vector<int> Reversed(const vector<int>& v){
    vector<int> reversed_dest(v.rbegin(), v.rend());
    return reversed_dest;
}
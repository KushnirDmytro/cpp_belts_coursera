//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


//Реализуйте функцию void Reverse(vector<int>& v), которая переставляет элементы вектора в обратном порядке.

/*
 *vector<int> numbers = {1, 5, 3, 4, 2};
Reverse(numbers);
// numbers должен оказаться равен {2, 4, 3, 5, 1}
 */


void Reverse(vector<int>& v){
    reverse(v.begin(), v.end());
}
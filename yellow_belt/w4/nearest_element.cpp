//
// Created by dkushn on 18.08.19.
//

//
// Created by dkushn on 14.08.19.
//

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
set<int>::const_iterator FindNearestElement(
        const set<int>& numbers,
        int border){
    auto equal_or_greater = numbers.lower_bound(border);
    if (equal_or_greater == numbers.begin() ){
        return equal_or_greater;
    }
    auto last_less = prev(equal_or_greater);
    if(equal_or_greater == numbers.end()){
        return last_less;
    }
    bool left_element =  abs(*last_less - border)  <=  abs(*equal_or_greater - border) ;
    return left_element ? last_less : equal_or_greater ;
}
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел


int main() {
    set<int> numbers = {1, 4, 6};
    cout <<
         *FindNearestElement(numbers, 0) << " " <<
         *FindNearestElement(numbers, 3) << " " <<
         *FindNearestElement(numbers, 5) << " " <<
         *FindNearestElement(numbers, 6) << " " <<
         *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}


/*
 1 4 4 6 6
1
 * */
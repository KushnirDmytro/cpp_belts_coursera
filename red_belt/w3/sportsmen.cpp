//
// Created by dkushn on 10.09.19.
//

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    size_t requests;
    cin >> requests;
    list<size_t> sportsmen;
    size_t new_number;
    size_t stand_after;
    vector<list<size_t>::iterator> known{100000, sportsmen.end()};
    for (size_t i = 0 ; i < requests; ++i){
        cin >> new_number >> stand_after;
        known[new_number] = sportsmen.insert(known[stand_after], new_number);
    }

    for (const auto& el: sportsmen){
        cout << el << ' ';
    }
    cout << endl;
}

/*

 5
42 0
17 42
13 0
123 42
5 13


 17 123 42 5 13
 * */
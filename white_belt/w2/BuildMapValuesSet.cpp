//
// Created by dkushn on 21.07.19.
//

//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
using namespace std;

/*
 in:
set<string> values = BuildMapValuesSet({
    {1, "odd"},
    {2, "even"},
    {3, "odd"},
    {4, "even"},
    {5, "odd"}
});

for (const string& value : values) {
  cout << value << endl;
}

 out:
even
odd

 */



//Напишите функцию BuildMapValuesSet, принимающую на вход словарь map<int, string> и возвращающую множество значений этого словаря:
// set<string> BuildMapValuesSet(const map<int, string>& m) {
//  // ...
//}

set<string> BuildMapValuesSet(const map<int, string>& m) {
    set<string> out;
    for (const auto& item: m){
        out.insert(item.second);
    }
    return out;
}

int main() {

    set<string> values = BuildMapValuesSet({
                                                   {1, "odd"},
                                                   {2, "even"},
                                                   {3, "odd"},
                                                   {4, "even"},
                                                   {5, "odd"}
                                           });
    for (const string& value : values) {
        cout << value << endl;
    }
}

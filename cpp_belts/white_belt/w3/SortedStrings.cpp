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


//Реализуйте класс, поддерживающий набор строк в отсортированном порядке. Класс должен содержать два публичных метода:
// class SortedStrings {
//public:
//  void AddString(const string& s) {
//    // добавить строку s в набор
//  }
//  vector<string> GetSortedStrings() {
//    // получить набор из всех добавленных строк в отсортированном порядке
//  }
//private:
//  // приватные поля
//};
class SortedStrings {
public:
    void AddString(const string& s) {
        auto it = find_if(strings_.begin(), strings_.end(), [s](const string &inner_string){ return inner_string > s;} );
        strings_.insert(it, s); // insert on first valid position
    }
    vector<string> GetSortedStrings() {
        return strings_;
    }
private:
    vector<string> strings_;
};


template<class T> ostream& operator<<(ostream& os, vector<T> v){
    for (const auto &s: v){
        cout << s << " ";
    }
    return os;
}
//
//void PrintSortedStrings(SortedStrings& strings) {
//    for (const string& s : strings.GetSortedStrings()) {
//        cout << s << " ";
//    }
//    cout << endl;
//}

//int main() {
//    SortedStrings strings;
//
//    strings.AddString("first");
//    strings.AddString("third");
//    strings.AddString("second");
//    PrintSortedStrings(strings);
//
//    strings.AddString("second");
//    PrintSortedStrings(strings);
//
//    // exepct:
//    // first second third
//    // first second second third
//    return 0;
//}
//

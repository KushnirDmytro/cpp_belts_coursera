//
// Created by dkushn on 22.07.19.
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


//Реализуйте класс ReversibleString, хранящий строку и поддерживающий методы Reverse
// для переворота строки и ToString для получения строки.

class ReversibleString{
    string str_;
public:
    ReversibleString(const string &str){
        str_ = str;
    }
    ReversibleString() = default;
    void Reverse(){
        reverse(str_.begin(), str_.end());
    }
    string ToString() const {
        return str_;
    }
};
//
//int main() {
//    ReversibleString s("live");
//    s.Reverse();
//    cout << s.ToString() << endl;
//
//    s.Reverse();
//    const ReversibleString& s_ref = s;
//    string tmp = s_ref.ToString();
//    cout << tmp << endl;
//
//    ReversibleString empty;
//    cout << '"' << empty.ToString() << '"' << endl;
//
//    return 0;
//}
//

// evil
//live
//""
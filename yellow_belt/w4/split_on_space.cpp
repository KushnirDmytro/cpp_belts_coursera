//
// Created by dkushn on 14.08.19.
//

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;


template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}


vector<string> SplitIntoWords(const string& s){

    vector<string> res;
    string buf_string;

    for (const auto& ch : s){
        if (isspace(ch)){
            res.push_back(buf_string);
            buf_string.resize(0);
        }  else {
            buf_string.push_back(ch);
        }
    }

    if (!buf_string.empty())
        res.push_back(buf_string);

    return res;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}

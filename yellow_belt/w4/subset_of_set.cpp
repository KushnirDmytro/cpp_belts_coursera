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


template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border){
    vector<T> out_vec(elements.size());
    auto end_it = copy_if(begin(elements), end(elements), begin(out_vec),
                          [border](const T &el){ return el > border;});
    out_vec.resize(end_it - begin(out_vec));
    return out_vec;
}

int main() {
    for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
        cout << x << " ";
    }
    cout << endl;

    string to_find = "Python";
    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
    return 0;
}

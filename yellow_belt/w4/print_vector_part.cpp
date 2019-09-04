//
// Created by dkushn on 14.08.19.
//

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &v){
    bool first{true};
    for(const auto &el: v){
        if (!first){
            os << ' ';
        }
        first = false;
        os << el;
    }
}

void PrintVectorPart(const vector<int>& numbers){
    auto first_negative = find_if(
            begin(numbers),
            end(numbers),
            [](const int &el){
                return el < 0;
            });
    for (auto it = first_negative; it != begin(numbers); ){
        cout << *(--it) << ' ';
    }
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}
#include<iostream>
#include<vector>
#include<utility>
#include<map>
using namespace std;

template <typename Key, typename Val> Val& GetRefStrict(map<Key, Val> &m, Key k){
    if (m.find(k) == m.end())
        throw runtime_error("no element found");
    return m[k];
}

//
//int main(){
//    map<int, string> m = {{0, "value"}};
//    string& item = GetRefStrict(m, 0);
//    item = "newvalue";
//    cout << m[0] << endl; // выведет newvalue
//}

#include<iostream>
#include<vector>
#include<utility>
#include<map>
using namespace std;


// Предварительное объявление шаблонных функций
template<typename T> vector<T> Sqr(vector<T> v);
template<typename T1, typename T2> map<T1, T2> Sqr(map<T1, T2> m);
template<typename T1, typename T2> pair<T1, T2> Sqr(pair<T1, T2> p);
template<typename T> T Sqr(T x);


template<typename T> T Sqr(T x){
    return x * x;
}


template<typename T1, typename T2> pair<T1, T2> Sqr(pair<T1, T2> p){
    return make_pair(Sqr(p.first), Sqr(p.second));
}

template<typename T> vector<T> Sqr(vector<T> v){
    for (auto & el: v){
        el = Sqr(el);
    }
    return v;
}

template<typename T1, typename T2> map<T1, T2> Sqr(map<T1, T2> m){
    for (auto & el: m){
        el.second = Sqr(el.second);
    }
    return m;
}


//
//int main(){
//    // Пример вызова функции
//    vector<int> v = {1, 2, 3};
//    cout << "vector:";
//    for (int x : Sqr(v)) {
//        cout << ' ' << x;
//    }
//    cout << endl;
//
//    map<int, pair<int, int>> map_of_pairs = {
//            {4, {2, 2}},
//            {7, {4, 3}}
//    };
//    cout << "map of pairs:" << endl;
//    for (const auto& x : Sqr(map_of_pairs)) {
//        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
//    }
//
//}

/*
vector: 1 4 9
map of pairs:
4 4 4
7 16 9
 * */
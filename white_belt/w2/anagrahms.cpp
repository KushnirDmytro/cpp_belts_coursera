//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
using namespace std;


//Слова называются анаграммами друг друга, если одно из них можно получить перестановкой букв в другом.
// Например, слово «eat» можно получить перестановкой букв слова «tea», поэтому эти слова являются анаграммами друг друга.
// Даны пары слов, проверьте для каждой из них, являются ли слова этой пары анаграммами друг друга.
//
//Указание
//Один из способов проверки того, являются ли слова анаграммами друг друга, заключается в следующем.
// Для каждого слова с помощью словаря подсчитаем, сколько раз в нём встречается каждая буква.
// Если для обоих слов эти словари равны (а это проверяется с помощью обычного оператора ==), то слова являются анаграммами друг друга, в противном случае не являются.
//
//При этом построение такого словаря по слову удобно вынести в отдельную функцию BuildCharCounters.
//
//Формат ввода
//Сначала дано число пар слов N, затем в N строках содержатся пары слов, которые необходимо проверить.
// Гарантируется, что все слова состоят лишь из строчных латинских букв.
//
//Формат вывода
//Выведите N строк: для каждой введённой пары слов YES, если эти слова являются анаграммами, и NO в противном случае.


/*
 in:
3
eat tea
find search
master stream

 out:
 YES
NO
YES
 */


template<class T> ostream& operator<<(ostream& os, vector<T> v){
    for (const auto &s: v){
        cout << s << " ";
    }
    return os;
}

template <class K, class V> ostream& operator <<(ostream& os, const map<K,V> &m){
    for (const auto& item: m){
        cout << item.first << ":" << item.second << endl;
    }
    return os;
}

map <char, int> BuildCharCounters(string s){
    map<char, int> ch_count;
    for(const char& ch: s){
        ++ch_count[ch];
    }
    return ch_count;
}

int main() {


    int N;
    cin >> N;
    string A, B;

    for (int i = 0; i < N; ++i){
        cin >> A >> B;

        map<char, int> A_count = BuildCharCounters(A);
        map<char, int> B_count = BuildCharCounters(B);
//
//        cout << A << endl;
//        cout << A_count << endl;
//        cout << B << endl;
//        cout << B_count << endl;

        if (A_count == B_count){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }

}

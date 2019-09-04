//
// Created by dkushn on 20.07.19.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;


//Напишите функцию, которая
//
//называется PalindromFilter
//возвращает vector<string>
//принимает vector<string> words и int minLength и возвращает все строки из вектора words, которые являются палиндромами и имеют длину не меньше minLength
//Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.

/*
words	minLength	результат
abacaba, aba	5	abacaba
abacaba, aba	2	abacaba, aba
weew, bro, code	4	weew

 */


bool IsPalindrom(const string &str){
    size_t beg{0}, end{str.size() - 1};
    if (end == 0){
        return true;
    }
    bool is_palindrom{true};
    const size_t old_end = end;
    while (beg <= end && is_palindrom && end <= old_end){
        is_palindrom = str[beg] == str[end];
        ++beg;
        --end;
    }
    return is_palindrom;
}

vector<string> PalindromFilter(vector<string> words, int minLength){
    vector<string> filtered;
    for (const string& word: words){
        if( word.length() >= minLength && IsPalindrom (word)){
            filtered.push_back(word);
        }
    }
    return filtered;
}

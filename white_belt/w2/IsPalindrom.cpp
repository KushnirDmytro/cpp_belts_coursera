//
// Created by dkushn on 20.07.19.
//
#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;


//Напишите функцию, которая
//
//называется IsPalindrom
//возвращает bool
//принимает параметр типа string и возвращает, является ли переданная строка палиндромом
//Палиндром - это слово или фраза, которые одинаково читаются слева направо и справа налево. Пустая строка является палиндромом.

/*
Аргумент функции	Результат
madam	true
gentleman	false
X	true

 */


bool IsPalindrom(const string &str){
    size_t beg{0}, end{str.size() - 1}; // caution, minus one on unsigned int
    if (str.empty() || end == 0){
        return true; // empty and one char length case
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


//int main() {
////    cout << IsPalindrom("madam")  << endl;
////    cout << IsPalindrom("gentleman")  << endl;
////    cout << IsPalindrom("X")  << endl;
////    cout << IsPalindrom("")  << endl;
//}
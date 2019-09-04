//
// Created by dkushn on 20.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


//Напишите функцию MoveStrings, которая принимает два вектора строк,
// source и destination, и дописывает все строки из первого вектора в конец второго.
// После выполнения функции вектор source должен оказаться пустым.
//
//Чтобы очистить содержимое вектора, надо вызвать у него метод clear:

/*
 *vector<string> source = {"a", "b", "c"};
vector<string> destination = {"z"};
MoveStrings(source, destination);
// source должен оказаться пустым
// destination должен содержать строки "z", "a", "b", "c" именно в таком порядке
 */


void MoveStrings(vector<string> &source, vector<string> &destination){
    copy(source.begin(), source.end(), back_inserter(destination));
    source.clear();
}
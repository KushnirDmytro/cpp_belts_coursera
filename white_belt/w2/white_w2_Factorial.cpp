//
// Created by dkushn on 20.07.19.
//

#include <iostream>
#include <vector>

using namespace std;


//Напишите функцию, которая
//
//называется Factorial
//возвращает int
//принимает int и возвращает факториал своего аргумента. Гарантируется, что аргумент функции по модулю не превышает 10. Для отрицательных аргументов функция должна возвращать 1.

/*
 * Аргумент функции	Результат
1	1
-2	1
4	24

 */


int Factorial(int arg){
    if (arg <= 0){
        return 1;
    }
    else{
        return arg * Factorial(arg - 1);
    }
}


int main() {
}
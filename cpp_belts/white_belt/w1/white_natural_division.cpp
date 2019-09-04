//
// Created by dkushn on 20.07.19.
//

#include <iostream>
#include <cmath>

using namespace std;

//Дано два натуральных числа A и B, не превышающих 1 000 000. Напишите программу, которая вычисляет целую часть частного от деления A на B.
//
//Если B = 0, выведите "Impossible".


/*
 * stdin	stdout
10 2	5
3 5	0
11 0	Impossible

 */


int main() {

    int A, B;

    cin >> A >> B;

    if (B == 0){
        cout << "Impossible" << endl;
        return 0;
    } else {
        cout << A / B << endl;
    }

    return 0;
}
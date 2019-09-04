//
// Created by dkushn on 20.07.19.
//

#include <iostream>
#include <cmath>

using namespace std;

//В stdin даны два натуральных числа. Выведите в stdout их наибольший общий делитель.


/*
stdin	stdout
25 27	1
12 16	4
13 13	13

 */


unsigned int gcd (unsigned int a, unsigned int b) {
    return (b == 0) ? a : gcd (b, a % b);
}

int main() {

    unsigned int a, b;

    cin >> a >> b;

    cout << gcd(a, b) << endl;

    return 0;
}
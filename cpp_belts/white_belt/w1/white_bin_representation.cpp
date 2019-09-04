//
// Created by dkushn on 20.07.19.
//

#include <iostream>
#include <vector>

using namespace std;


//На вход дано целое положительное число N. Выведите его в двоичной системе счисления без ведущих нулей.


/*
stdin	stdout
5	101
32	100000
1	1
 */



int main() {

    unsigned int N;

    cin >> N;

    vector<int> bin_numbers;

    while(N != 0){
        bin_numbers.push_back(N % 2);
        N /= 2;
    }
    for(int i = bin_numbers.size() - 1; i >= 0; --i){
        cout << bin_numbers[i];
    }
    cout << endl;

    return 0;
}
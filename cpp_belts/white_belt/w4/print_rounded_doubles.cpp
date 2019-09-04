//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;


//В файле input.txt записаны вещественные числа, по одному на строчку.
// На стандартный вывод напечатайте эти числа в том же порядке, по одному на строке, но сделайте так,
// чтобы у каждого из них было ровно три знака после десятичной точки
// (округление производится по стандартным правилам, т.е. 0.1234 округляется до 0.123, а 0.1235 до 0.124).

/*
in:
 5
0.34567
10.4

 3.33353
3.333
3.3


 out:
 5.000
0.346
10.400


 3.334
3.333
3.300
 */

int main()
{
    ifstream i_file("input.txt");
    double val_buf;
    cout <<  fixed << setprecision(3);
    while (i_file >> val_buf){
         // val_buf = roundf(val_buf * 1000) / 1000;
        cout << val_buf << endl;
    }
    return 0;
}
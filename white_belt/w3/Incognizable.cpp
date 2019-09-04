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
using namespace std;

struct Incognizable{
    int a;
    int b = 0;
    Incognizable(): a{0}, b{0} {};
    Incognizable(int arg1): a{arg1}, b{0} {};
    Incognizable(int arg1, int arg2): a{arg1}, b{arg2} {};

};

int main() {
    Incognizable a;
    Incognizable b = {};
    Incognizable c = {0};
    Incognizable d = {0, 1};
    return 0;
}

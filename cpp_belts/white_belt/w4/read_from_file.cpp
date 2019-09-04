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

using namespace std;


//В этом задании вам предстоит написать две небольшие программы. Каждый пункт - отдельная задача, решение отправляйте в поле с соответствующим номером.
//
//Часть 1
//Ваша программа должна считать содержимое файла input.txt и напечатать его на экран без изменений. Гарантируется, что содержимое файла input.txt заканчивается переводом строки.
//
//Пример
// Keep calm
//and
//learn C++

int main()
{
    ifstream i_file("input.txt");
    string line_buf;
    if (i_file){
        while (getline(i_file, line_buf)){
            cout << line_buf << endl;
        }
    }
    return 0;
}
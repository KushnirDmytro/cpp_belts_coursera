//
// Created by dkushn on 12.09.19.
//

#include <iostream>
#include <sstream>

#include "stats.h"



//void PrSV(string_view sv){ cout << "[" << sv.substr(0, sv.size()) << ']' << endl;}

HttpRequest ParseRequest(string_view line){
    HttpRequest hr;
//    PrSV(line);

    line.remove_prefix(line.find_first_not_of(' '));
    auto space = line.find(' ');
    hr.method = {line.begin(), space};
    line.remove_prefix(space);
    line.remove_prefix( line.find_first_not_of(' '));
    space = line.find(' ');

    hr.uri = {line.begin(), space};
    line.remove_prefix(space);
    line.remove_prefix(line.find_first_not_of(' '));

    auto last_char = line.find_last_not_of(' ');
    hr.protocol = {line.begin(), last_char + 1};
    return hr;

}


void Stats::AddMethod(string_view method) {
    if (METHODS_COUNT.find(method) == METHODS_COUNT.end()){
        ++METHODS_COUNT["UNKNOWN"];
    } else {
        ++METHODS_COUNT[method];
    }
}


void Stats::AddUri(string_view uri) {
    if (URI_COUNT.find(uri) == URI_COUNT.end()){
        ++URI_COUNT["unknown"];
    } else {
        ++URI_COUNT[uri];
    }
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return METHODS_COUNT;
}

const map<string_view, int> &Stats::GetUriStats() const {
    return URI_COUNT;
}

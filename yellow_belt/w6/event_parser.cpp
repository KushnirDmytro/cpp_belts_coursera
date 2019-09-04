//
// Created by dkushn on 04.09.19.
//

#include <string>
#include <algorithm>

#include "event_parser.h"

using namespace std;

string ParseEvent(istream& is) {
    string event_notation;
    getline(is, event_notation);
    event_notation.erase(event_notation.begin(), find_if_not(event_notation.begin(), event_notation.end(), ::isspace));
    return event_notation;
}
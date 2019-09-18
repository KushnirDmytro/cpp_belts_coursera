//
// Created by dkushn on 18.09.19.
//

#ifndef CPP_BELTS_TOTAL_DURATION_H
#define CPP_BELTS_TOTAL_DURATION_H

#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include "profile.h"

using namespace std;
using namespace chrono;


struct TotalDuration {
    string message;
    steady_clock::duration value;
    explicit TotalDuration(const string& msg = "")
            : message(msg + ": ")
            , value(0)
    {
    }
    ~TotalDuration() {
        ostringstream os;
        os << message
           << duration_cast<milliseconds>(value).count()
           << " ms" << endl;
        cerr << os.str();
    }
};

struct AllDurations{
    TotalDuration* reading_time;
    TotalDuration* making_index_time;
    TotalDuration* sorting_time;
    TotalDuration* printing_time;
};

class AddDuration {
public:
    explicit AddDuration(steady_clock::duration& dest)
            : add_to(dest)
            , start(steady_clock::now())
    {
    }
    explicit AddDuration(TotalDuration& dest)
            : AddDuration(dest.value)
    {
    }
    ~AddDuration() {
        add_to += steady_clock::now() - start;
    }
private:
    steady_clock::duration& add_to;
    steady_clock::time_point start;
};

#define ADD_DURATION(value) \
AddDuration UNIQ_ID(__LINE__){value};



#endif //CPP_BELTS_TOTAL_DURATION_H

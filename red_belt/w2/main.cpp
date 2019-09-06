//
// Created by dkushn on 06.09.19.
//
#include <iostream>
#include <sstream>
#include "learner.cpp"
#include "test_runner.h"
#include "profile.h"

using namespace std;


void TestSortingSpeed() {

    Learner learner;
    vector<string> new_words{};
    size_t n_words = 10000;
    for (size_t i = 0; i < n_words; ++i){
        new_words.push_back(to_string(i));
    }
    {
        LOG_DURATION("LEARNING " )
        cout << learner.Learn(new_words) << "\n";
        cout << "=== known words ===\n";
        for (auto word : learner.KnownWords()) {
//            cout << word << "\n";
        }
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSortingSpeed);

//    Learner learner;
//    string line;
//    while (getline(cin, line)) {
//        vector<string> words;
//        stringstream ss(line);
//        string word;
//        while (ss >> word) {
//            words.push_back(word);
//        }
//        cout << learner.Learn(words) << "\n";
//    }
//    cout << "=== known words ===\n";
//    for (auto word : learner.KnownWords()) {
//        cout << word << "\n";
//    }
}
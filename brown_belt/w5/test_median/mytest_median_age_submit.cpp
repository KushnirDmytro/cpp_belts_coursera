//
// Created by dkushn on 15.10.19.
//

#include "test_runner.h"

#include <vector>

ostream& operator<<(ostream& os, Gender gen){
    os << (gen == Gender::MALE);
    return os;
}


bool operator<(const Person& lhs, const Person &rhs){
    return lhs.age < rhs.age;
}

void assert_stream_has_vector_cntnt(const vector<string> &expected, stringstream &oss ){
    string buf;
    auto it = expected.begin();
    while (getline(oss, buf) ){
        cout << buf << endl;
        cout << *it << endl;
        ASSERT_EQUAL(*(it), buf);
        it = next(it, 1);
    }
};



void B3_and_4_reading_order_preserved(){
vector<Person> ps{
        {31, Gender::FEMALE, false},
        {31, Gender::MALE, false},
        {31, Gender::FEMALE, true},
        {31, Gender::MALE, true}
};

vector<string> input {
    "4 \n",
    "31 0 0 \n",
    "31 1 0 \n",
    "31 0 1 \n",
    "31 1 1 \n"
};
stringstream iss;
for (const auto &per_str : input){
    iss << per_str;
}
    vector<Person> result = ReadPersons(iss);
    ASSERT_EQUAL(result, ps);
};

//    bool operator==(const AgeStats &lhs, const AgeStats &rhs){
//        return lhs.employed_females == rhs.employed_females &&
//        lhs.employed_males == rhs.employed_males &&
//        lhs.females == rhs.females &&
//        lhs.males == rhs.males &&
//        lhs.total == rhs.total &&
//        lhs.unemployed_females == rhs.unemployed_females &&
//        lhs.unemployed_males == rhs.unemployed_males;
//    }

void test5_6ComputeMedianEnds(){
    vector<Person> persons {
            {31, Gender::MALE, false},
            {40, Gender::FEMALE, true},
            {24, Gender::MALE, true},
            {20, Gender::FEMALE, true},
            {80, Gender::FEMALE, false},
            {78, Gender::MALE, false},
            {10, Gender::FEMALE, false},
            {55, Gender::MALE, true}
    };
    AgeStats as = ComputeStats(persons);
    AgeStats as_expect {
        40,
        40,
        55,
        40,
        80,
        55,
        78
    };
    ASSERT( as_expect ==  as);
}

void test1_EmptyRange(){
    vector<Person> persons {
    };
    int stat = ComputeMedianAge(persons.begin(), persons.end());

    ASSERT( stat == 0);
}

void test1_s1_range(){
    vector<Person> persons {
            {1, Gender::MALE, false}
    };
    int stat = ComputeMedianAge(persons.begin(), persons.end());

    ASSERT( stat == 1);
}

void test2_OddSizeRange(){
    vector<Person> persons {
            {1, Gender::MALE, false},
            {2, Gender::FEMALE, true},
            {3, Gender::MALE, true},
            {4, Gender::FEMALE, true},
            {5, Gender::FEMALE, false}
    };
    int stat = ComputeMedianAge(persons.begin(), persons.end());

    ASSERT( stat == 3);
}

void testSwapOrder(){
    AgeStats as_expect {
            40,
            40,
            55,
            40,
            80,
            55,
            78
    };
    stringstream ss;
    PrintStats(as_expect, ss);
    vector<string> expected {
            "Median age = 40",
            "Median age for females = 40",
            "Median age for males = 55",
            "Median age for employed females = 40",
            "Median age for unemployed females = 80",
            "Median age for employed males = 55",
            "Median age for unemployed males = 78"
    };
    assert_stream_has_vector_cntnt(expected, ss);
}

int main(){
    TestRunner tr;
//    RUN_TEST(tr, Test1);
    RUN_TEST(tr, test1_EmptyRange);
    RUN_TEST(tr, test2_OddSizeRange);
    RUN_TEST(tr, B3_and_4_reading_order_preserved);
    RUN_TEST(tr, test5_6ComputeMedianEnds);
    RUN_TEST(tr, testSwapOrder);
//    RunMedianAge(cin, cout);
}
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
//#include "white_belt/w3/PersonName.cpp"

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

//class Person {
//public:
//    // Вы можете вставлять сюда различные реализации класса,
//    // чтобы проверить, что ваши тесты пропускают корректный код
//    // и ловят некорректный
//    void ChangeFirstName(int year, const string& first_name) {
//    }
//    void ChangeLastName(int year, const string& last_name) {
//    }
//    string GetFullName(int year) {
//    }
//};

void testUnknownDefaultName(){
    Person p;
    AssertEqual(Person().GetFullName(0), "Incognito");
    p.ChangeFirstName(1, "A");
    AssertEqual(Person().GetFullName(0), "Incognito");
    p.ChangeLastName(2, "B");
    AssertEqual(Person().GetFullName(0), "Incognito");
};


void testKnownNameUnknownSurname(){
    Person p;
    string f_name = "A";
    p.ChangeFirstName(1, f_name);
    AssertEqual(p.GetFullName(2), f_name  + " with unknown last name");
    AssertEqual(p.GetFullName(1), f_name  + " with unknown last name");
    AssertEqual(p.GetFullName(0), "Incognito");
};

void testKnownSurnameUnknownName(){
    Person p;
    string l_name = "L";
    p.ChangeLastName(1, l_name);
    AssertEqual(p.GetFullName(2), l_name  + " with unknown first name");
    AssertEqual(p.GetFullName(1), l_name  + " with unknown first name");
    AssertEqual(p.GetFullName(0), "Incognito");
};

void testKnownNameAndSurname(){
    Person p;
    string f_name = "F";
    string l_name = "L";
    p.ChangeFirstName(1, f_name);
    p.ChangeLastName(2, l_name);
    AssertEqual(p.GetFullName(1), f_name  + " with unknown last name");
    AssertEqual(p.GetFullName(2), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(5), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(0), "Incognito");
};
void testKnownNameChangedTwice(){
    Person p;
    string f_name = "F";
    string l_name = "L";
    p.ChangeFirstName(1, f_name);
    p.ChangeLastName(2, l_name);
    AssertEqual(p.GetFullName(1), f_name  + " with unknown last name");
    AssertEqual(p.GetFullName(2), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(5), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(0), "Incognito");
    string f2_name = "F2";
    p.ChangeFirstName(10, f2_name);
    AssertEqual(p.GetFullName(2), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(1), f_name  + " with unknown last name");
    AssertEqual(p.GetFullName(10), f2_name  + " " + l_name);
    AssertEqual(p.GetFullName(11), f2_name  + " " + l_name);
};
void testKnownSrunameChangedTwice(){
    Person p;
    string f_name = "F";
    string l_name = "L";
    p.ChangeLastName(1, l_name);
    p.ChangeFirstName(2, f_name);

    AssertEqual(p.GetFullName(1), l_name  + " with unknown first name");
    AssertEqual(p.GetFullName(2), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(5), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(0), "Incognito");
    string l2_name = "L2";
    p.ChangeLastName(10, l2_name);
    AssertEqual(p.GetFullName(1), l_name  + " with unknown first name");
    AssertEqual(p.GetFullName(2), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(5), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(10), f_name  + " " + l2_name);
    AssertEqual(p.GetFullName(11), f_name  + " " + l2_name);
};

void testBothChangedTwice(){
    Person p;
    string f_name = "F";
    string l_name = "L";
    p.ChangeLastName(1, l_name);
    p.ChangeFirstName(2, f_name);

    AssertEqual(p.GetFullName(1), l_name  + " with unknown first name");
    AssertEqual(p.GetFullName(2), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(5), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(0), "Incognito");
    string l2_name = "L2";
    string f2_name = "F2";
    p.ChangeLastName(10, l2_name);
    AssertEqual(p.GetFullName(1), l_name  + " with unknown first name");
    AssertEqual(p.GetFullName(2), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(5), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(10), f_name  + " " + l2_name);
    AssertEqual(p.GetFullName(11), f_name  + " " + l2_name);
    p.ChangeFirstName(20, f2_name);
    AssertEqual(p.GetFullName(1), l_name  + " with unknown first name");
    AssertEqual(p.GetFullName(2), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(5), f_name  + " " + l_name);
    AssertEqual(p.GetFullName(10), f_name  + " " + l2_name);
    AssertEqual(p.GetFullName(11), f_name  + " " + l2_name);

    AssertEqual(p.GetFullName(20), f2_name  + " " + l2_name);
    AssertEqual(p.GetFullName(21), f2_name  + " " + l2_name);
};

int main() {
    TestRunner runner;
    runner.RunTest(testUnknownDefaultName, "testUnknownDefaultName");
    runner.RunTest(testKnownNameUnknownSurname, "testKnownNameUnknownSurname");
    runner.RunTest(testKnownSurnameUnknownName, "testKnownSurnameUnknownName");
    runner.RunTest(testKnownNameAndSurname, "testKnownNameAndSurname");
    runner.RunTest(testKnownNameChangedTwice, "testKnownNameChangedTwice");
    runner.RunTest(testKnownSrunameChangedTwice, "testKnownSrunameChangedTwice");
    runner.RunTest(testBothChangedTwice, "testBothChangedTwice");
    // добавьте сюда свои тесты
    return 0;
}

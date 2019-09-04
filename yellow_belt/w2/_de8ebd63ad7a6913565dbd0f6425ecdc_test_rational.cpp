#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
//#include "Rational.cpp"

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

//class Rational {
//public:
//  // Вы можете вставлять сюда различные реализации,
//  // чтобы проверить, что ваши тесты пропускают корректный код
//  // и ловят некорректный
//
//  Rational();
//  Rational(int numerator, int denominator) {
//  }
//
//  int Numerator() const {
//  }
//
//  int Denominator() const {
//  }
//};

void testDefaultRational(){
    AssertEqual(Rational().Numerator(), Rational(0,1).Numerator(), "Default constructor");
    AssertEqual(Rational().Denominator(), Rational(0,1).Denominator(), "Default constructor");
}

void testCustomCreationSign(){
    AssertEqual(Rational(1, 2).Numerator(), 1, "numberator == 1");
    AssertEqual(Rational(-1, 2).Numerator(), -1, "Numerator == -1");
    AssertEqual(Rational(0, 2).Numerator(), 0, "Numerator == 0");
    AssertEqual(Rational(1, 2).Numerator(), 1, "Numerator == 1");
    AssertEqual(Rational(-1, 2).Numerator(), -1, "Numerator == -1");
    AssertEqual(Rational(1, -2).Numerator(), -1, "Numerator == -1");
    AssertEqual(Rational(-1, -2).Numerator(), 1, "Numerator == 1");
    AssertEqual(Rational(1, -2).Numerator(), -1, "Numerator == -1");
    AssertEqual(Rational(1, -2).Denominator(), 2, "Denominator == 2");
    AssertEqual(Rational(-1, -2).Denominator(), 2, "Denominator == 2");
    AssertEqual(Rational(1, 2).Denominator(), 2, "Denominator == 2");
}

void testCustomCreationSimplify(){
    AssertEqual(Rational(1, 2).Numerator(), 1, "numberator == 1");
    AssertEqual(Rational(1, 2).Denominator(), 2, "Denominator == 2");

    AssertEqual(Rational(2, 4).Numerator(), 1, "numberator == 1");
    AssertEqual(Rational(2, 4).Denominator(), 2, "Denominator == 2");

    AssertEqual(Rational(-2, 4).Numerator(), -1, "numberator == -1");
    AssertEqual(Rational(-2, -4).Denominator(), 2, "Denominator == 1");
}

void testZeroNumerator(){
    AssertEqual(Rational(0, 2).Denominator(), 1, "Denominator == 1");
    AssertEqual(Rational(0, 1).Denominator(), 1, "Denominator == 1");
    AssertEqual(Rational(0, -2).Denominator(), 1, "Denominator == 1");
    AssertEqual(Rational(0, -1).Denominator(), 1, "Denominator == 1");
}

void testDenomValue(){
    AssertEqual(Rational(0, 2).Denominator(), 1, "Denom == 1");
    AssertEqual(Rational(0, -1).Denominator(), 1, "Denominator == 1");
    AssertEqual(Rational(1, 1).Denominator(), 1, "Denominator == 1");
    AssertEqual(Rational(0, -2).Denominator(), 1, "Numerator == 0");
}



//
//int main() {
//    Rational lhs, rhs;
//    string oper;
//    try{
//        cin >> lhs >> oper >> rhs;
//        perform_operation(known_ops[oper], lhs, rhs);
//    }
//    catch (invalid_argument& er){
//        cout << er.what() << endl;
//    }
//}

int main() {
    TestRunner runner;
    runner.RunTest(testDefaultRational, "testDefaultRational");
    runner.RunTest(testCustomCreationSign, "testCustomCreationSign");
    runner.RunTest(testCustomCreationSimplify, "testCustomCreationSimplify");
    runner.RunTest(testZeroNumerator, "testZeroNumerator");
    runner.RunTest(testDenomValue, "testDenomValue");
    // добавьте сюда свои тесты
    return 0;
}

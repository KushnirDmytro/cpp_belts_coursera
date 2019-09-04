#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
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



double eps = 0.0001;

double get_discriminant(double A, double B, double C){
    double det = B * B - 4 * A * C;
    return det;
}

bool is_eq(double v1, double v2){
    return abs(v1 - v2) <= eps;
}

struct solution{
    double x1, x2;
    bool exist {false};
    bool exist2 {false};
};

solution solve_eq(const double &A, const double &B, const double &C){
    solution rez;

    if (is_eq(C, 0.0)){
        if (is_eq(A, 0.0)){
            rez.x1 = 0;
            rez.exist = true;
            return rez;
        }
        else{
            rez.x1 = 0;
            rez.x2 = -B / A;
            rez.exist2 = true;
            rez.exist = true;
            return rez;
        }
    }

    if (is_eq(A, 0.0)){
        if (is_eq(B, 0.0)) {
            return rez;
        }
        else {
            rez.exist = true;
            rez.x1 = -C / B;
            return rez;
        }
    }

    double discrim = get_discriminant(A, B, C);

    if (discrim + eps < 0.0) {
        return rez; // no real value roots;
    }
    else {
        rez.exist = true;
        if (is_eq(discrim, 0.0)){
            rez.x1 = - B / (2 * A);
            return rez;
        }
        else{
            rez.exist2 = true;
            rez.x1 = (- B + sqrt(discrim)) / (2 * A);
            rez.x2 = (- B - sqrt(discrim)) / (2 * A);
            return rez;
        }
    }

}




int GetDistinctRealRootCount(double a, double b, double c) {
    solution sol = solve_eq(a, b, c);

    if (sol.exist){
//        cout << sol.x1;
        if (sol.exist2) {
//            cout << " " << sol.x2;
            return 2;
        } else {
            return 1;
        }
        cout << endl;
    }

    return 0;
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
}


void testNoRoots(){
    AssertEqual(GetDistinctRealRootCount(1,0,1), 0, "x^2 + 1 =0 has no real roots");
    AssertEqual(GetDistinctRealRootCount(2,0,1), 0, "2x^2 + 1 =0 has no real roots");
}
void testRootsWhileConstant(){
    AssertEqual(GetDistinctRealRootCount(0,0,1), 0, "1=0 has no real roots");
    AssertEqual(GetDistinctRealRootCount(0,0,-1), 0, "-1=0 has no real roots");
}
void testLinearRoots(){
    AssertEqual(GetDistinctRealRootCount(0,1,1), 1, "x + 1=0 has one root");
    AssertEqual(GetDistinctRealRootCount(0,-2,1), 1, "-2x + 1=0 has one real ");
    AssertEqual(GetDistinctRealRootCount(0,3,-5), 1, "3x - 5=0 has one real root");
    AssertEqual(GetDistinctRealRootCount(0,-3,-5), 1, "-3x - 5=0 has one real root");
}
void testQadraticTwoRoots(){
    AssertEqual(GetDistinctRealRootCount(1,2,0.5), 2, "2x^2 + 2x + 1 = 0 has two roots");
}

void testQadraticOneRoot(){
    AssertEqual(GetDistinctRealRootCount(1,-2,1), 1, "x^2 - 2 + 1 = 0 has 1 real root, Discriminant is zero");
    AssertEqual(GetDistinctRealRootCount(4,-28,49), 1, "4 x^2 - 28 + 49 = 0 has 1 real root, Discriminant is zero");
}

void testQadraticNoRoots(){
    AssertEqual(GetDistinctRealRootCount(1,1,1), 0, "x^2 + 1 + 1 =0 has no real roots, Discriminant is negative");
    AssertEqual(GetDistinctRealRootCount(1,-1,1), 0, "x^2 - 1 + 1 =0 has no real roots, Discriminant is negative");
}



int main() {
    TestRunner runner;
    runner.RunTest(testNoRoots, "testNoRoots");
    runner.RunTest(testRootsWhileConstant, "testRootsWhileCon");
    runner.RunTest(testQadraticNoRoots, "testQadraticNoRoots");
    runner.RunTest(testQadraticOneRoot, "testQadraticOneRoot");
    runner.RunTest(testQadraticTwoRoots, "testQadraticTwoRoots");
    runner.RunTest(testLinearRoots, "testLinearRoots");
    // добавьте сюда свои тесты
    return 0;
}

#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;




unsigned int gcd (unsigned int a, unsigned int b) {
    return (b == 0) ? a : gcd (b, a % b);
}

class Rational {
public:
    Rational() : num{0}, denom{1}{
    }

    Rational(int numerator, int denominator) {
        bool is_neg = ( numerator <= 0 && denominator > 0 ) || ( numerator >=0 && denominator < 0 );
        int gcd_val = gcd(abs(numerator), abs(denominator));
        if (gcd_val > 1){
            num = is_neg ? ( int(abs(numerator)) * -1 )/ gcd_val  : abs(numerator) / gcd_val;
            denom = abs(denominator) / gcd_val;
        }
        else{
            num = is_neg ? abs(numerator)  * -1 : abs(numerator);
            denom = abs(denominator);
        }
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return denom;
    }

private:
    int num;
    unsigned int denom;
    // Добавьте поля
};

bool operator==(const Rational &lhs, const Rational &rhs){
    return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational &lhs, const Rational &rhs){
    return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator() ,
                    rhs.Denominator() * lhs.Denominator());
}

Rational operator-(const Rational &lhs, const Rational &rhs){
    return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator() ,
                    rhs.Denominator() * lhs.Denominator());
}

Rational operator*(const Rational &lhs, const Rational &rhs){
    return Rational(lhs.Numerator() * rhs.Numerator(),
                    rhs.Denominator() * lhs.Denominator());
}
Rational operator/(const Rational &lhs, const Rational &rhs){
    return Rational(lhs.Numerator() * rhs.Denominator(),
                    lhs.Denominator() * rhs.Numerator());
}


istream& operator>>(istream& is, Rational& rat){
    int numer_buf, denom_buf;
    if(is >> numer_buf){
        is.ignore(1,'/');
        if (is >> denom_buf)
            rat = Rational(numer_buf, denom_buf);
    }
    return is;
}

ostream& operator<<(ostream& os, const Rational &rat){
    os << rat.Numerator() << '/' << rat.Denominator();
    return os;
}
bool operator<(const Rational& lhs, const Rational& rhs){
    return lhs.Numerator() * rhs.Denominator() < lhs.Denominator() * rhs.Numerator();
}
bool operator>(const Rational& lhs, const Rational& rhs){
    return ! (lhs < rhs || lhs == rhs);
}
bool operator!=(const Rational& lhs, const Rational& rhs){
    return ! (lhs == rhs);
}


// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

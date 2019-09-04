//
// Created by dkushn on 26.07.19.
//

#include <iostream>
#include <exception>
#include <map>
using namespace std;

unsigned int gcd (unsigned int a, unsigned int b) {
    return (b == 0) ? a : gcd (b, a % b);
}

class Rational {
public:
    Rational() : num{0}, denom{1}{
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0){
            throw invalid_argument("Invalid argument");
        }
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

Rational operator/(const Rational &lhs, const Rational &rhs){
    if (rhs.Numerator() == 0){
        throw domain_error("Division by zero");
    }
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

enum operation{
    plus, minus, mul, divide, eq, uneq, lt, gt
};

map<string, operation> known_ops{
        {"+", operation::plus},
        {"-", operation::minus},
        {"*", operation::mul},
        {"/", operation::divide},
        {"==", operation::eq},
        {"!=", operation::uneq},
        {"<", operation::lt},
        {">", operation::gt}
};

void try_read_rational(Rational& rat_buf){
    try{
        cin >> rat_buf;
    } catch (invalid_argument& er){
        cout << er.what() << endl;
    }
}

void perform_operation(operation op, const Rational& lhs, const Rational& rhs){
    switch (op){
        case (operation::plus):
            cout << lhs + rhs << endl;
            break;
        case (operation::minus):
            cout << lhs - rhs << endl;
            break;
        case (operation::mul):
            cout << lhs * rhs << endl;
            break;
        case (operation::divide):
            try{
                cout << lhs / rhs << endl;
            }
            catch (domain_error& div_err){
                cout << div_err.what() << endl;
            }
            break;
        case (operation::eq):
            cout << (lhs == rhs) << endl;
            break;
        case (operation::uneq):
            cout << (lhs != rhs) << endl;
            break;
        case (operation::lt):
            cout << (lhs < rhs) << endl;
            break;
        case (operation::gt):
            cout << (lhs > rhs) << endl;
            break;
    }
}

int main() {
    Rational lhs, rhs;
    string oper;
    try{
        cin >> lhs >> oper >> rhs;
        perform_operation(known_ops[oper], lhs, rhs);
    }
    catch (invalid_argument& er){
        cout << er.what() << endl;
    }
}
//stdin	stdout
//1/2 + 1/3	5/6
//1/2 + 5/0	Invalid argument
//4/5 / 0/8	Division by zero
#include <iostream>
#include <sstream>
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

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}

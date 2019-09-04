#include <iostream>
using namespace std;
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


// Реализуйте для класса Rational операторы * и /

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}

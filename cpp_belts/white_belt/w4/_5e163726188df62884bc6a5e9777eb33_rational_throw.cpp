#include <iostream>
#include <exception>

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
            throw invalid_argument("Creating rational with 0 as denominator");
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

Rational operator/(const Rational &lhs, const Rational &rhs){
    if (rhs.Numerator() == 0){
        throw domain_error("Division by zero occurred");
    }
    return Rational(lhs.Numerator() * rhs.Denominator(),
                    lhs.Denominator() * rhs.Numerator());
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}

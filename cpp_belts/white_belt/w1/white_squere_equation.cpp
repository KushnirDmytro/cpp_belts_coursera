//
// Created by dkushn on 20.07.19.
//

#include <iostream>
#include <cmath>

using namespace std;

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

int main() {

    double A, B, C;

    std::cin >> A >> B >> C;

    solution sol = solve_eq(A, B, C);

    if (sol.exist){
        cout << sol.x1;
        if (sol.exist2) {
            cout << " " << sol.x2;
        }
        cout << endl;
    }

    return 0;
}
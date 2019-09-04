//
// Created by dkushn on 21.08.19.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <map>
#include <iomanip>
#include <cmath>

using namespace std;



class Figure{
protected:
    static constexpr double PI {3.14};
public:
    Figure() = default;
    virtual string Name() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
};

class Rect : public Figure{
    const uint h_;
    const uint w_;
public:
    Rect(uint h, uint w)
            : h_{h}, w_{w}
    {
    }

    string Name() override {
        return "RECT";
    };
    double Perimeter() override {
        return w_ + w_ + h_ + h_;
    };

    double Area() override {
        return w_ * h_;
    };
};

class Triangle : public Figure{
    const uint a_;
    const uint b_;
    const uint c_;
public:

    Triangle(uint a, uint b, uint c)
            : a_{a}, b_{b}, c_{c}
    {
    }

    string Name() override {
        return "TRIANGLE";
    };
    double Perimeter() override {
        return a_ + b_ + c_;
    };

    double Area() override {  //   Heron's formula
        double p = Perimeter() / 2.0;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    };
};

class Circle : public Figure{
    const uint r_;
public:

    explicit Circle(uint r)
            : r_{r}
    {
    }

    string Name() override {
        return "CIRCLE";
    };
    double Perimeter() override {
        return 2 * Figure::PI * r_ ;
    };

    double Area() override {
        return PI * r_ * r_;
    };
};

enum class commands{
    ADD, PRINT
};


static map<string, commands> coms{
        {"ADD",  commands::ADD},
        {"PRINT",  commands::PRINT}
};

enum class figures{
    RECT, TRIANGLE, CIRCLE
};

static map<string, figures> figs{
        {"RECT",  figures::RECT},
        {"TRIANGLE",  figures::TRIANGLE},
        {"CIRCLE",  figures::CIRCLE}
};

shared_ptr<Figure> CreateFigure(istringstream &is){
    string figure_name;
    is >> figure_name;
    figures this_fig = figs[figure_name];
    switch (this_fig){
        case (figures ::TRIANGLE):
            uint a, b, c;
            is >> a >> b >> c;
            return make_shared<Triangle>(a, b, c);
        case (figures :: RECT):
            uint h, w;
            is >> h >> w;
            return make_shared<Rect>(h, w);
        case (figures :: CIRCLE):
            uint r;
            is >> r;
            return make_shared<Circle>(r);
    }
}


int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
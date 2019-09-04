//
// Created by dkushn on 22.07.19.
//

//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
using namespace std;

// Реализуйте рассказанный на лекции класс Function, позволяющий создавать, вычислять и инвертировать функцию, состоящую из следующих элементарных операций:
//
//прибавить вещественное число x;
//вычесть вещественное число x.
//При этом необходимо объявить константными все методы, которые по сути такими являются.
//struct Image {
//    double quality;
//    double freshness;
//    double rating;
//};
//
//struct Params {
//    double a;
//    double b;
//    double c;
//};

class Function{


public:
    void AddPart(char new_symbol, double new_param){
        parts.emplace_back(new_symbol, new_param);
    }
    double Apply(const double &arg) const {
        double rezult {arg};
        for(auto &oper: this->parts){
            rezult = oper.Apply(rezult);
        }
        return rezult;
    }

    void Invert(){
        for(auto &part: this->parts){
            part.Invert();
        }
        reverse(parts.begin(), parts.end());
    }

private:

    class FunctionPart{
        char oper_symbol;
        double param;
    public:
        FunctionPart(const char new_oper_symbol, const double &new_param) :
                oper_symbol{new_oper_symbol},
                param{new_param}{}
        double Apply(const double &arg) const {
            switch (oper_symbol){
                case ('+'):
                    return arg + param;
                case ('-'):
                    return arg - param;
            }
        }

        void Invert(){
            switch (this->oper_symbol){
                case ('+'):{
                    this->oper_symbol = '-';
                    return;
                }
                case ('-'):{
                    this->oper_symbol = '+';
                    return;
                }
            }
        }

    };

    vector<FunctionPart> parts;

};
//
//Function MakeWeightFunction(const Params& params,
//                            const Image& image) {
//    Function function;
//    function.AddPart('-', image.freshness * params.a + params.b);
//    function.AddPart('+', image.rating * params.c);
//    return function;
//}
//
//double ComputeImageWeight(const Params& params, const Image& image) {
//    Function function = MakeWeightFunction(params, image);
//    return function.Apply(image.quality);
//}
//
//double ComputeQualityByWeight(const Params& params,
//                              const Image& image,
//                              double weight) {
//    Function function = MakeWeightFunction(params, image);
//    function.Invert();
//    return function.Apply(weight);
//}
//
//int main() {
//    Image image = {10, 2, 6};
//    Params params = {4, 2, 6};
//    cout << ComputeImageWeight(params, image) << endl;
//    cout << ComputeQualityByWeight(params, image, 46) << endl;
//    return 0;
//}

// 36
//20
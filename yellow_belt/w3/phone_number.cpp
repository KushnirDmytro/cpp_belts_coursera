//
// Created by dkushn on 13.08.19.
//

#include <sstream>
#include <iomanip>
#include "phone_number.h"


string PhoneNumber::GetInternationalNumber() const {
    stringstream ss;
    ss << '+' << GetCountryCode()  << '-' <<  GetCityCode() << '-' << GetLocalNumber();
    return ss.str();
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

PhoneNumber::PhoneNumber(const string &international_number) {

    bool format_ok{true};
    stringstream ss(international_number);
    format_ok &= (ss.peek() == '+');
    if (format_ok){
        try{
            format_ok &= ss.get() == '+';
            getline(ss, country_code_, '-');
            getline(ss, city_code_, '-');
            getline(ss, local_number_);
            format_ok &= ss.peek();
        }catch (const error_t &e){
            throw invalid_argument("wrong number format");
        }
    }
    format_ok &= country_code_.size() && city_code_.size() && local_number_.size();
    if (!format_ok) {
        throw invalid_argument("wrong number format");
    }

}

//int main() {
//    vector<string> ok {
//        "+7-495-111-22-33",
//        "+3-1-2",
//        "+7-495-1112233",
//        "+323-22-460002",
//        "+1-2-coursera-cpp"
//    };
//    for (const string &num: ok){
//        PhoneNumber ph(num);
//        cout << ph.GetCountryCode() << endl;
//        cout << ph.GetCityCode() << endl;
//        cout << ph.GetLocalNumber() << endl;
//        cout << ph.GetInternationalNumber() << endl << endl;
//    }
//    vector<string> not_ok {
//            "1-2-333",
//            "+7-1233"
//    };
//    for (const string &num: not_ok){
//        try{PhoneNumber ph(num);}catch (const exception &e){cout << e.what() << endl;}
//    }
//
//    // добавьте сюда свои тесты
//    return 0;
//}

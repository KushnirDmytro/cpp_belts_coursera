#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;



int main() {
    size_t ndays;
    cin >> ndays;

    double d_ndays(ndays);
    double mean_temp{0};
    vector<int> days(ndays);
    for (auto & day: days){
        cin >> day;
        mean_temp += day / d_ndays;
    }
    vector<size_t> overmean_days_indexes;
    for (size_t i = 0; i < ndays; ++i){
        if (days[i] > mean_temp){
            overmean_days_indexes.emplace_back(i);
        }
    }
    cout << overmean_days_indexes.size() << endl;
    for (const auto &day: overmean_days_indexes){
        cout << day << ' ';
    }
    cout << endl;
    return 0;
}


/*

 * */
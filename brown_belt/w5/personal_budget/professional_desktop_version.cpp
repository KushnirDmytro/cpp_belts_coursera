#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <map>
#include <unordered_map>
//#include <test_runner.h>

using namespace std;
static const int SECONDS_IN_DAY = 60 * 60 * 24;

vector<string> splitStringBy(const string& s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim))
    {
        result.push_back(item);
    }
    return result;
}
tm parseTime(const std::string& ts)
{
    std::tm t;
    const auto dateParts = splitStringBy(ts, '-');
    stringstream(dateParts[0]) >> t.tm_year;
    t.tm_year -= 1900;
    stringstream(dateParts[1]) >> t.tm_mon;
    t.tm_mon -= 1;
    stringstream(dateParts[2]) >> t.tm_mday;
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    t.tm_isdst = 0;
    return t;
}

class PersonalBudgetManager
{
    struct Record
    {
        Record(std::tm newDate, const double newEarning)
            :
            timeMoment_{mktime(&newDate)},
            earning_{newEarning}
        {}
        const time_t timeMoment_;
        const double earning_{0.0};
    };

    enum class QueryType
    {
        ComputeIncome,
        Earn,
        PayTax
    };
public:

    double ComputeIncome(const time_t from, const time_t to) const
    {
        double accum{0.0};
        for(time_t d{from}; d <= to; d += SECONDS_IN_DAY)
        {
            auto earnigngRecord = earnings_.find(d);
            if(earnigngRecord != earnings_.end())
                accum += earnings_.at(d);
            auto spendingRecord = spendings_.find(d);
            if(spendingRecord != spendings_.end())
                accum -= spendings_.at(d);
        }
        return accum;
    }
    void Earn(const time_t from, const time_t to, const double value)
    {
        const double secondsDiff = difftime(to, from);
        const size_t daysDiff = secondsDiff / SECONDS_IN_DAY;
        const double daylyEarning = value / (daysDiff + 1);

        for(time_t d{from}; d <= to; d += SECONDS_IN_DAY) // TODO: speedup taking keys set intersection
        {
            earnings_[d] += daylyEarning;
        }
    }
    void Spend(const time_t from, const time_t to, const double value)
    {
        const double secondsDiff = difftime(to, from);
        const size_t daysDiff = secondsDiff / SECONDS_IN_DAY;
        const double daylySpendings = value / (daysDiff + 1);

        for(time_t d{from}; d <= to; d += SECONDS_IN_DAY)
        {
            spendings_[d] += daylySpendings;
        }
    }
    void PayTax(const time_t& from, const time_t& to, const int taxRate)
    {
        double percentsLeft = (100 - taxRate) / 100.0;
        for (time_t d {from}; d <= to; d+= SECONDS_IN_DAY)
        {
            auto item = earnings_.find(d);
            if(item != earnings_.end())
                item->second *= percentsLeft;
        }
    }
private:
    std::unordered_map<time_t, double> earnings_;
    std::unordered_map<time_t, double> spendings_;
};

void RunPersonnalBudgetManager(istream& is, ostream& os)
{
    PersonalBudgetManager bm;
    int query_count;
    is >> query_count;
    //int i = 0;
    for(int query_id = 0; query_id < query_count; ++query_id)
    {
        //cout << ++i << endl;
        string query_type,
               dateFrom,
               dateTo;
        is >> query_type
            >> dateFrom
            >> dateTo;

        auto timestampFrom{parseTime(dateFrom)};
        auto timestampTo{parseTime(dateTo)};
        const auto timeFrom{mktime(&timestampFrom)};
        const auto timeTo{mktime(&timestampTo)};

        if (query_type == "ComputeIncome")
        {
            os << setprecision(25) << bm.ComputeIncome(timeFrom, timeTo) << std::endl;
        }
        else if (query_type == "Earn")
        {
            int value;
            is >> value;
            bm.Earn(timeFrom, timeTo, value);
        }
        else if(query_type == "Spend")
        {
            int value;
            is >> value;
            bm.Spend(timeFrom, timeTo, value);
        }
        else if (query_type == "PayTax")
        {
            int taxRate;
            is >> taxRate;
            bm.PayTax(timeFrom, timeTo, taxRate);
        }
    }
}


//void TestPersonnalBudgetDesktopVersion()
//{
//    const vector<string> queries{
//            "8\n",
//            "Earn          2000-01-02 2000-01-06 20\n",
//            "ComputeIncome 2000-01-01 2001-01-01\n",
//            "PayTax        2000-01-02 2000-01-03 13\n",
//            "ComputeIncome 2000-01-01 2001-01-01\n",
//            "Spend         2000-12-30 2001-01-02 14\n",
//            "ComputeIncome 2000-01-01 2001-01-01\n",
//            "PayTax        2000-12-30 2000-12-30 13\n",
//            "ComputeIncome 2000-01-01 2001-01-01\n"
//    };
//
//    const vector<double> expected_results{
//            20,
//            18.96,
//            8.46,
//            8.46
//    };
//
//    stringstream is;
//    for(const auto& q : queries)
//    {
//        is << q;
//    }
//    stringstream expected;
//    for(const auto& er : expected_results)
//    {
//        expected << er << '\n';
//    }
//
//    stringstream os;
//    RunPersonnalBudgetManager(is, os);
//    double number;
//    for(const auto& d : expected_results)
//    {
//        os >> number;
//        //cout << "expect: " << d;
//        //cout << "have: " << number << endl;
//        ASSERT_EQUAL(d, number);
//    }
//}


int main()
{
// Для ускорения чтения данных отключается синхронизация
// cin и cout с stdio,
// а также выполняется отвязка cin от cout
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    //ostringstream os;
    //TestRunner tr;
    //RUN_TEST(tr, TestPersonnalBudgetDesktopVersion);
    RunPersonnalBudgetManager(cin, cout);
    return 0;
}

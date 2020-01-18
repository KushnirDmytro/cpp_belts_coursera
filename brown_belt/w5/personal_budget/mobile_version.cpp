#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <test_runner.h>

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
struct Request
{
    enum class Type 
    {
        ComputeIncome,
        Earn, 
        Spend, 
        PayTax
    };

    Type requestType_;
    time_t from_;
    time_t to_;
    int money_;
};

std::unordered_map<string_view, const Request::Type> AsRequestType
{
    {"ComputeIncome", Request::Type::ComputeIncome},
    {"Earn", Request::Type::Earn},
    {"Spend", Request::Type::Spend},
    {"PayTax", Request::Type::PayTax}
};

std::vector<Request> ReadRequests (std::istream& stream)
{
    int query_count;
    stream >> query_count;
    std::vector<Request> requests;
    requests.reserve(query_count);
    for(int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type,
            dateFrom,
            dateTo;
        stream >> query_type
            >> dateFrom
            >> dateTo;

        auto timestampFrom{parseTime(dateFrom)};
        auto timestampTo{parseTime(dateTo)};
        const auto timeFrom{mktime(&timestampFrom)};
        const auto timeTo{mktime(&timestampTo)};
        const Request::Type requestType = AsRequestType[query_type];
        int money;
        switch (requestType)
        {
            case(Request::Type::ComputeIncome):
                requests.emplace_back(Request{requestType, timeFrom, timeTo, 0});
                break;
            case(Request::Type::Earn): 
            case(Request::Type::Spend): 
            case(Request::Type::PayTax): 
                stream >> money;
                requests.emplace_back(Request{requestType, timeFrom, timeTo, money});
                break;
        }
    }
    return requests;
}


class PersonalBudgetManager
{
    struct AccountRecord
    {
        double earned_{0.0};
        double spent_{0.0};
    };
    
public:
    double ComputeIncome(const time_t from, const time_t to)
    {
        double accum1{0.0};
        double accum2{0.0};
        //unordered_map<time_t, AccountRecord> filteredRequests = records_;

        // TODO: use ordered sets and then run from lower bound to upper_bound +1
        //accumulate
        //std::accumulate()
        //std::accumulate();
        //earnTimestamps_
        for_each(allTimestamps_.lower_bound(from), allTimestamps_.upper_bound(to),
                 [&]( const auto key ) 
                 {
                     const auto rec = records_[key];
                     accum1 += (rec.earned_ - rec.spent_);
                 }
        );
        return accum1;
    }
    void Earn(const time_t from, const time_t to, const double value)
    {
        const double secondsDiff = difftime(to, from);
        const size_t daysDiff = secondsDiff / SECONDS_IN_DAY;
        const double daylyEarning = value / (daysDiff + 1);
        //this->earnTimestamps_.lower_bound(from);
        //this->earnTimestamps_.lower_bound(to);
        for(time_t d{from}; d <= to; d += SECONDS_IN_DAY) // TODO: speedup taking keys set intersection, not overall
        {
            records_[d].earned_ += daylyEarning;
            earnTimestamps_.insert(d);
            allTimestamps_.insert(d);
        }
    }
    void Spend(const time_t from, const time_t to, const double value)
    {
        const double secondsDiff = difftime(to, from);
        const size_t daysDiff = secondsDiff / SECONDS_IN_DAY;
        const double daylySpendings = value / (daysDiff + 1);
        for(time_t d{from}; d <= to; d += SECONDS_IN_DAY)
        {
            records_[d].spent_ += daylySpendings;
            allTimestamps_.insert(d);
        }
    }
    void PayTax(const time_t& from, const time_t& to, const int taxRate)
    {
        const double percentsLeft = (100 - taxRate) / 100.0;

        for_each(earnTimestamps_.lower_bound(from), earnTimestamps_.upper_bound(to),
                 [&](const auto& key) {
                     if (key >= from && key <= to)
                         records_[key].earned_ *= percentsLeft;
                 });

    }
private:

    unordered_map<time_t, AccountRecord> IntersectionOfMaps(const unordered_map<time_t, AccountRecord>& m1, const unordered_map<time_t, AccountRecord>& m2)
    {
        const auto& sMap = m1.size() <= m2.size() ? m1 : m2;
        const auto& lMap = m1.size() > m2.size() ? m1 : m2;
        unordered_map<time_t, AccountRecord> intersection;
        for (const auto& sMapEl : sMap)
        {
            auto lMapIter = lMap.find(sMapEl.first);
            if (lMapIter != lMap.end())
            {
                intersection.emplace(sMapEl);
            }
        }
        return intersection;
    }
    std::set<time_t> allTimestamps_;
    std::set<time_t> earnTimestamps_;
    std::map<time_t, AccountRecord> records_;
};

void RunPersonnalBudgetManager(istream& is, ostream& os)
{
    PersonalBudgetManager bm;
    const vector<Request> requests = ReadRequests(is);
    for (const auto& request : requests)
    {
        switch (request.requestType_)
        {
        case (Request::Type::ComputeIncome):
            os << setprecision(25) << bm.ComputeIncome(request.from_, request.to_) << std::endl; break;
        case (Request::Type::Earn):
            bm.Earn(request.from_, request.to_, request.money_); break;
        case (Request::Type::Spend):
            bm.Spend(request.from_, request.to_, request.money_); break;
        case (Request::Type::PayTax):
            bm.PayTax(request.from_, request.to_, request.money_); break;
        }
    }
}

void TestPersonnalBudgetDesktopVersion()
{
    const vector<string> queries{
            "8\n",
            "Earn          2000-01-02 2000-01-06 20\n",
            "ComputeIncome 2000-01-01 2001-01-01\n",
            "PayTax        2000-01-02 2000-01-03 13\n",
            "ComputeIncome 2000-01-01 2001-01-01\n",
            "Spend         2000-12-30 2001-01-02 14\n",
            "ComputeIncome 2000-01-01 2001-01-01\n",
            "PayTax        2000-12-30 2000-12-30 13\n",
            "ComputeIncome 2000-01-01 2001-01-01\n"
    };

    const vector<double> expected_results{
            20,
            18.96,
            8.46,
            8.46
    };

    stringstream is;
    for(const auto& q : queries)
    {
        is << q;
    }
    stringstream expected;
    for(const auto& er : expected_results)
    {
        expected << er << '\n';
    }

    stringstream os;
    RunPersonnalBudgetManager(is, os);
    double number;
    for(const auto& d : expected_results)
    {
        os >> number;
        //cout << "expect: " << d;
        //cout << "have: " << number << endl;
        ASSERT_EQUAL(d, number);
    }
}

int main()
{
// Для ускорения чтения данных отключается синхронизация
// cin и cout с stdio,
// а также выполняется отвязка cin от cout
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    ostringstream os;
    TestRunner tr;
    RUN_TEST(tr, TestPersonnalBudgetDesktopVersion);
    cin.precision(25);
    RunPersonnalBudgetManager(cin, cout);
    return 0;
}

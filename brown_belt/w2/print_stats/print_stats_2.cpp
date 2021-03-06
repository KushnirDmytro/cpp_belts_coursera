#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <sstream>

#include "test_runner.h"

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  int age, income;
  bool is_male;
};

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

enum class Command{
    AGE,
    WEALTHY,
    POPULAR_NAME
};

static const unordered_map<string, Command> getCommand{
        {"AGE", Command ::AGE},
        {"WEALTHY", Command ::WEALTHY},
        {"POPULAR_NAME", Command ::POPULAR_NAME},
};




void RunGenderStatistics(char gender,  ostream& os, const vector<Person>& sorted_name_male, const vector<Person>& sorted_name_female ){
    const vector<Person>& people = gender == 'M' ? sorted_name_male : sorted_name_female;
    IteratorRange range{
            begin(people),
            end(people)
    };

    if (range.begin() == range.end()) {
        os << "No people of gender " << gender << '\n';
    } else {
        const string* most_popular_name = &range.begin()->name;
        int count = 1;
        for (auto i = range.begin(); i != range.end(); ) {
            auto same_name_end = find_if_not(i, range.end(), [i](const Person& p) {
                return p.name == i->name;
            });
            auto cur_name_count = std::distance(i, same_name_end);
            if (cur_name_count > count) {
                count = cur_name_count;
                most_popular_name = &i->name;
            }
            i = same_name_end;
        }
        os << "Most popular name among people of gender " << gender << " is "
           << *most_popular_name << '\n';
    }
}

    void RunWealthStatistics(int count,  ostream& os,  const vector<Person> &wealth_sorted_people){
    auto head = Head(wealth_sorted_people, count);

    int total_income = accumulate(
            head.begin(), head.end(), 0, [](int cur, const Person& p) {
                return p.income + cur;
            }
    );
    os << "Top-" << count << " people have total income " << total_income << '\n';
}

void RunAgeStatistics(int adult_age,  ostream& os, const vector<Person> &people){
    auto adult_begin = lower_bound(
            begin(people), end(people), adult_age, [](const Person& lhs, int age) {
                return lhs.age < age;
            }
    );
    os << "There are " << std::distance(adult_begin, end(people))
       << " adult people for maturity age " << adult_age << '\n';
}


void RunStatistics(istream &istr, ostream& os){
    vector<Person> buf_people = ReadPeople(istr);

    const vector<Person> sorted_age_people = [](vector<Person> buf_people){
        sort(begin(buf_people), end(buf_people), [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        });
        return buf_people;
    }(buf_people);

    const vector<Person> sorted_wealth_people = [](vector<Person> buf_people){
        sort(begin(buf_people), end(buf_people), [](const Person& lhs, const Person& rhs) {
                 return lhs.income > rhs.income;
             }
        );
        return buf_people;
    }(sorted_age_people);

    vector<Person> sorted_name_men_people;
    vector<Person> sorted_name_women_people;

    copy_if(begin(buf_people), end(buf_people), back_inserter(sorted_name_men_people), [](const Person& p){ return p.is_male;});
    copy_if(begin(buf_people), end(buf_people), back_inserter(sorted_name_women_people), [](const Person& p){ return !p.is_male;});
    sort(sorted_name_men_people.begin(), sorted_name_men_people.end(), [](const Person& lhs, const Person& rhs) {
        return lhs.name < rhs.name;
    });
    sort(sorted_name_women_people.begin(), sorted_name_women_people.end(), [](const Person& lhs, const Person& rhs) {
        return lhs.name < rhs.name;
    });

    stringstream temp_os;
    RunGenderStatistics('W', temp_os, sorted_name_men_people, sorted_name_women_people);
    string cached_female_name_request{temp_os.str()};
    temp_os.str("");
    RunGenderStatistics('M', temp_os, sorted_name_men_people, sorted_name_women_people);
    string cached_male_name_request{temp_os.str()};



    Command next_command;
    for (string command_buf;  istr >> command_buf; ) {
        next_command = getCommand.at(command_buf);
        switch (next_command){
            case (Command::AGE):{
                int adult_age;
                istr >> adult_age;
                RunAgeStatistics(adult_age, os, sorted_age_people);
                break;
            }
            case (Command::WEALTHY):{
                int count;
                istr >> count;
                RunWealthStatistics(count, os, sorted_wealth_people);

                break;
            }
            case (Command::POPULAR_NAME):{
                char gender;
                istr >> gender;
                if (gender == 'M')
                    os << cached_male_name_request;
                else
                    os << cached_female_name_request;
//                RunGenderStatistics(gender, os, sorted_name_men_people, sorted_name_women_people);
                break;
            }
        }
    }
}

void TestOneInputOneOutput(){
    vector<string> in_v{"11\n",
                        "Ivan 25 1000 M\n"
                        "Olga 30 623 W\n"
                        "Sergey 24 825 M\n"
                        "Maria 42 1254 W\n"
                        "Mikhail 15 215 M\n"
                        "Oleg 18 230 M\n"
                        "Denis 53 8965 M\n"
                        "Maxim 37 9050 M\n"
                        "Ivan 47 19050 M\n"
                        "Ivan 17 50 M\n"
                        "Olga 23 550 W\n"
                        "AGE 18\n"
                        "AGE 25\n"
                        "WEALTHY 5\n"
                        "POPULAR_NAME M\n"
                        "POPULAR_NAME W\n"
    };
    vector<string> expected{
            "There are 9 adult people for maturity age 18",
            "There are 6 adult people for maturity age 25",
            "Top-5 people have total income 39319",
            "Most popular name among people of gender M is Ivan",
            "Most popular name among people of gender W is Olga"
    };
    stringstream ios;
    for (const auto &line: in_v)
        ios << line;

    stringstream os;
    RunStatistics(ios, os);

    string respond;
    for (size_t i{0}; i < expected.size() && getline(os, respond); ++i){
        ASSERT_EQUAL(expected[i], respond);
    }
}

void TestDoubleRequest(){
    vector<string> in_v{"11\n",
                        "Ivan 25 1000 M\n"
                        "Olga 30 623 W\n"
                        "Sergey 24 825 M\n"
                        "Maria 42 1254 W\n"
                        "Mikhail 15 215 M\n"
                        "Oleg 18 230 M\n"
                        "Denis 53 8965 M\n"
                        "Maxim 37 9050 M\n"
                        "Ivan 47 19050 M\n"
                        "Ivan 17 50 M\n"
                        "Olga 23 550 W\n"
                        "AGE 18\n"
                        "AGE 25\n"
                        "WEALTHY 5\n"
                        "POPULAR_NAME M\n",
                        "AGE 18\n"
                        "AGE 25\n"
                        "WEALTHY 5\n"
                        "POPULAR_NAME M\n"
    };
    vector<string> expected{
            "There are 9 adult people for maturity age 18",
            "There are 6 adult people for maturity age 25",
            "Top-5 people have total income 39319",
            "Most popular name among people of gender M is Ivan",
            "There are 9 adult people for maturity age 18",
            "There are 6 adult people for maturity age 25",
            "Top-5 people have total income 39319",
            "Most popular name among people of gender M is Ivan"
    };
    stringstream ios;
    for (const auto &line: in_v)
        ios << line;

    stringstream os;
    RunStatistics(ios, os);
    string respond;
    for (size_t i{0}; i < expected.size() && getline(os, respond); ++i){
        ASSERT_EQUAL(expected[i], respond);
    }
}


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestOneInputOneOutput);
    RUN_TEST(tr, TestDoubleRequest);

    RunStatistics(cin, cout); // usual execution
}

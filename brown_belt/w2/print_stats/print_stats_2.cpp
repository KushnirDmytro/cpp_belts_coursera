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

void RunStatistics(istream &istr, ostream& os){
    vector<Person> people = ReadPeople(istr);

    sort(begin(people), end(people), [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
    });

    Command next_command;
    for (string command_buf;  istr >> command_buf; ) {
        next_command = getCommand.at(command_buf);
        switch (next_command){
            case (Command::AGE):{
                int adult_age;
                istr >> adult_age;

                auto adult_begin = lower_bound(
                        begin(people), end(people), adult_age, [](const Person& lhs, int age) {
                            return lhs.age < age;
                        }
                );

                os << "There are " << std::distance(adult_begin, end(people))
                     << " adult people for maturity age " << adult_age << '\n';
                break;
            }
            case (Command::WEALTHY):{
                int count;
                istr >> count;

                auto head = Head(people, count);

                partial_sort(
                        head.begin(), head.end(), end(people), [](const Person& lhs, const Person& rhs) {
                            return lhs.income > rhs.income;
                        }
                );

                int total_income = accumulate(
                        head.begin(), head.end(), 0, [](int cur, Person& p) {
                            return p.income += cur;
                        }
                );
                os << "Top-" << count << " people have total income " << total_income << '\n';
                break;
            }
            case (Command::POPULAR_NAME):{
                char gender;
                istr >> gender;

                IteratorRange range{
                        begin(people),
                        partition(begin(people), end(people), [gender](Person& p) {
                            return p.is_male = (gender == 'M');
                        })
                };
                if (range.begin() == range.end()) {
                    os << "No people of gender " << gender << '\n';
                } else {
                    sort(range.begin(), range.end(), [](const Person& lhs, const Person& rhs) {
                        return lhs.name < rhs.name;
                    });
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
    };
    vector<string> expected{
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
    int i = 0;
    while(getline(os, respond)){
        ASSERT_EQUAL(expected[i++], respond);
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
    int i = 0;
    while(getline(os, respond)){
//        cout << respond << endl;
        ASSERT_EQUAL(expected[i++], respond);
    }
}


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestOneInputOneOutput);
    RUN_TEST(tr, TestDoubleRequest);

    RunStatistics(cin, cout); // usual execution
}

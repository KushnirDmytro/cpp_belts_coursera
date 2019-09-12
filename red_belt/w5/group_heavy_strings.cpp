#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <memory>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

class CH{
    const string v;
public:
    CH(string v) : v{v} {

    }

    CH(const CH &rhs) : v{rhs.v}{
        cout << "Copied el " << v << endl;
    }

    CH(const CH &&rhs) : v{move(rhs.v)}{
        cout << "Moved el " << v << endl;
    }

    CH& operator=(const CH &rhs){
        *this = CH(rhs.v);
        cout << "Copied Moved el " << v << endl;
        return *this;
    }

    bool operator<(const CH &rhs) const { return v < rhs.v;}
    bool operator==(const CH &rhs) const { return v == rhs.v;}
};

template <typename CH>
class STR{
    vector<CH> data;

public:

    STR(const STR &&rhs) : data{move(rhs.data)}{
        cout << "STR moved" << endl;
    }
    STR(const STR &rhs) : data{rhs.data}{
        cout << "STR copied" << endl;
    }

    bool operator<(const STR &rhs) const { return data < rhs.data;}
    bool operator==(const STR &rhs)const { return data == rhs.data;}

    typedef CH value_type;
//    valiue_type = typename CH;
    STR(vector<CH> data) : data{move(data)} {}
    auto begin() { return data.begin();}
    auto end() { return data.end();}

    auto begin() const { return data.begin();}
    auto end() const { return data.end();}
};


template <typename String>
map<Char<String>, size_t > MakeAlphabet(vector<String> strings){
    map<Char<String>, size_t > abet;
    for(auto &st: strings)
        for(auto &ch: st){
            if (abet.find(ch) == abet.end()){
                abet[move(ch)] = abet.size();
            }
        }
    return abet;
}


template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    using Group = vector<String>;

    auto abet = MakeAlphabet(move(vector<String>{strings}));

    map< set<size_t >, vector<String*>> known_sets;

    for ( String &st : strings){
        set<size_t> abet_indx_set;

        for( auto &ch: st)
            abet_indx_set.insert(abet.at(ch));
        known_sets[abet_indx_set].push_back(&st);
    }

    vector<Group> res;
    for (auto &set_to_vec : known_sets){
        res.emplace_back();
        for(auto &string_ptr: set_to_vec.second){
            res.back().push_back(move(*string_ptr));
        }
    }

    return res;
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

void TestGroupingCH() {
    STR<CH> s1 = {{string("A")}};
    vector<STR<CH>> strings = { {{string("A")}} };
    cout << "BEGIN OF ALGO" << endl;
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 1);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
//    ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
//    ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
//    ASSERT_EQUAL(groups[2], vector<string>({"port"}));
//    ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
//  RUN_TEST(tr, TestGroupingCH);
  return 0;
}

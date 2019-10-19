#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <iterator>

#include "test_runner.h"


using namespace std;
using ParsedDomain = vector<string_view>;

template <typename Container>
void SplitString(std::string_view str, Container& container, char delim = '.')
{
    while(!str.empty()){
        const auto& delim_pos = str.find(delim);
        container.emplace_back(str.substr(0 , delim_pos));
        str.remove_prefix(
                delim_pos == str.npos ? str.size() : min(delim_pos + 1, str.size()) );
    }
}



inline bool IsSubdomain(
        ParsedDomain par_subdomain,
        ParsedDomain par_domain){
    return par_subdomain.size() >= par_domain.size() &&
    equal(par_domain.begin(), par_domain.end(), par_subdomain.begin());
}


vector<string> ReadDomains(istream& is) {
  size_t count;
  is >> count;

  vector<string> domains { count };

  for (string& domain : domains)
  {
        is >> domain;
        reverse(domain.begin(), domain.end());
  }
  return domains;
}

inline void PrintResult(ostream& oss, const bool res){
    if (res){
        oss << "Good" << endl;
    } else {
        oss << "Bad" << endl;
    }
}

void CheckedDomainStatus(
        const vector<string> &subdomains,
        const set<ParsedDomain> &banned_domains,
        ostream& oss){
    for (const string& subdomain : subdomains) {
        bool is_good{true};

        ParsedDomain parsed_subdomain;
        SplitString(subdomain, parsed_subdomain);

        const auto last_token {parsed_subdomain.empty() ? "" : parsed_subdomain.front()};

        for(
                auto it = banned_domains.lower_bound({ last_token});
                is_good && it != banned_domains.end() && (*it).front() == last_token;
                it = next(it)
                        )
        {
            is_good = !IsSubdomain(parsed_subdomain, *it);
        }
        PrintResult(oss, is_good);
    }
}


void assert_stream_has_vector_cntnt(const vector<string> &expected, stringstream &oss ){
    string buf;
    auto it = expected.begin();
    while (getline(oss, buf) || it != expected.end() ){
        ASSERT_EQUAL(*(it), buf);
        it = next(it, 1);
    }
};

set<ParsedDomain> ParseDomains(const vector<string>& banned_domains){
    set<ParsedDomain> parsed_domains;
    for (const auto &domain_sting : banned_domains){
        ParsedDomain new_parsed;
        SplitString(domain_sting, new_parsed);
        parsed_domains.emplace(new_parsed);
    }
    return parsed_domains;
}

void RunDomainCheck(const vector<string>& in_data, const vector<string>& expected){
    stringstream iss;
    for (const string& s: in_data){
        iss << s << '\n';
    }

    const vector<string> banned_domains = ReadDomains(iss);
    set<ParsedDomain> parsed_domains = ParseDomains(banned_domains);
    const vector<string> domains_to_check = ReadDomains(iss);

    stringstream oss;

    CheckedDomainStatus(domains_to_check, parsed_domains, oss);

    assert_stream_has_vector_cntnt(expected, oss);
}



void TestB(){

    static const vector<string> in_data {
            "1",
            "ya.ru",
            "2",
            "ya.ru",
            "ya.ru"
    };

    static const vector<string> expected {
            "Bad",
            "Bad"
    };

    RunDomainCheck(in_data, expected);

};

void TestA(){

    static const vector<string> in_data {
            "4",
            "ya.ru",
            "maps.me",
            "m.ya.ru",
            "com",
            "9",
            "ya.ru",
            "com",
            "ya.com",
            "m.maps.me",
            "moscow.m.ya.ru",
            "maps.com ",
            "maps.com",
            "maps.ru",
            "ya.ya"
    };

    static const vector<string> expected {
            "Bad",
            "Bad",
            "Bad",
            "Bad",
            "Bad",
            "Bad",
            "Bad",
            "Good",
            "Good"
    };

    RunDomainCheck(in_data, expected);

};


void TestEmpty(){

    static const vector<string> in_data {
            "0",
            "9",
            "ya.ru",
            "com",
            "ya.com",
            "m.maps.me",
            "moscow.m.ya.ru",
            "maps.com",
            "maps.com",
            "maps.ru",
            "ya.ya"
    };

    static const vector<string> expected {
            "Good",
            "Good",
            "Good",
            "Good",
            "Good",
            "Good",
            "Good",
            "Good",
            "Good"
    };

    RunDomainCheck(in_data, expected);

};


void TestEmpty2(){

    static const vector<string> in_data {
            "9",
            "ya.ru",
            "com",
            "ya.com",
            "m.maps.me",
            "moscow.m.ya.ru",
            "maps.com",
            "maps.com",
            "maps.ru",
            "ya.ya",
            "0"
    };

    static const vector<string> expected {

    };
    RunDomainCheck(in_data, expected);

};

void TestEmptyDomainString(){

    static const vector<string> in_data {
            "9",
            "ya.ru",
            "com",
            "ya.com",
            "m.maps.me",
            "moscow.m.ya.ru",
            "maps.com",
            "maps.com",
            "maps.ru",
            "ya.ya",
            "1",
            ""
    };

    static const vector<string> expected {
        "Good"
    };

    RunDomainCheck(in_data, expected);

};


void TestEmptySubdomainString(){

    static const vector<string> in_data {
            "1",
            "l",
            "1",
            "ll"
    };

    static const vector<string> expected {
            "Good"
    };
    RunDomainCheck(in_data, expected);


};



int main() {
    TestRunner tr;
    RUN_TEST(tr, TestA);
    RUN_TEST(tr, TestB);
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestEmpty2);
    RUN_TEST(tr, TestEmptyDomainString);
    RUN_TEST(tr, TestEmptySubdomainString);

   const vector<string> banned_domains = ReadDomains(cin);
   const set<string> banned_domains_set = {move_iterator(banned_domains.begin()), move_iterator(banned_domains.end())};

   const vector<string> domains_to_check = ReadDomains(cin);
   CheckedDomainStatus(domains_to_check, ParseDomains(banned_domains), cout);

   return 0;
}
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

#include "test_runner.h"


using namespace std;


bool IsSubdomain(string_view subdomain, string_view domain) {

    size_t domain_size = domain.size();
    size_t subdomain_size = subdomain.size();
    if (domain_size > subdomain_size)
        return false;

    string_view subdomains_domain = subdomain.substr(0, domain_size);
    return subdomains_domain == domain && (domain_size == subdomain_size || subdomain[domain_size] == '.') ;
}


vector<string> ReadDomains(istream& is) {
  size_t count;
  is >> count;

  vector<string> domains{count};

  for (string& domain : domains)
  {
        is >> domain;
        reverse(domain.begin(), domain.end());
  }
  return domains;
}

void CheckedDomainStatus(const vector<string> &domains_to_check, const set<string> &banned_domains, ostream& oss){
    for (const string_view subdomain : domains_to_check) {
        bool is_good{true};
//        if (subdomain.empty()) continue;
         for (const string_view bd: banned_domains){
             bool both_empty = subdomain.empty() && bd.empty();
            if ( (both_empty) ||  (!subdomain.empty() && !bd.empty() && IsSubdomain(subdomain, bd))){
                is_good = false;
                break;
            }
        }
        if (is_good){
            oss << "Good" << endl;
        } else {
            oss << "Bad" << endl;
        }
    }
}


void assert_stream_has_vector_cntnt(const vector<string> &expected, stringstream &oss ){
    string buf;
    auto it = expected.begin();
    while (getline(oss, buf) || it != expected.end() ){
//        cout << buf << endl;
//        cout << *it << endl;
        ASSERT_EQUAL(*(it), buf);
        it = next(it, 1);
    }
};



void RunDomainCheck(const vector<string>& in_data, const vector<string>& expected){
    stringstream iss;
    for (const string& s: in_data){
        iss << s << '\n';
    }

    const vector<string> banned_domains = ReadDomains(iss);
    const set<string> banned_domains_set = {move_iterator(banned_domains.begin()), move_iterator(banned_domains.end())};
    const vector<string> domains_to_check = ReadDomains(iss);

    stringstream oss;

    CheckedDomainStatus(domains_to_check, banned_domains_set, oss);

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

  CheckedDomainStatus(domains_to_check, banned_domains_set, cout);
  return 0;
}
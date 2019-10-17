#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;


bool IsSubdomain(string_view subdomain, string_view domain) {

    size_t domain_size = domain.size();
    size_t subdomain_size = subdomain.size();
    if (domain_size > subdomain_size)
        return false;

    string_view subdomains_domain = subdomain.substr(subdomain_size - domain_size, domain_size);
    return subdomains_domain == domain;

//    return (domain == subdomain)

  auto i = subdomain.size() - 1;
  auto j = domain.size() - 1;
  while (i >= 0 && j >= 0) {
    if (subdomain[i--] != domain[j--]) {
      return false;
    }
  }
  return (i < 0 && domain[j] == '.')
      || (j < 0 && subdomain[i] == '.');
}


vector<string> ReadDomains(istream& is) {
  size_t count;
  is >> count;

  vector<string> domains{count};

  for (string& domain : domains)
  {
        is >> domain;
  }
  return domains;
}

void CheckedDomainStatus(const vector<string> &domains_to_check, const vector<string> &banned_domains){
    for (const string_view subdomain : domains_to_check) {
        bool is_good{true};
        for (const string_view bd: banned_domains){
            if (IsSubdomain(subdomain, bd)){
                is_good = false;
                break;
            }
        }
        if (is_good){
            cout << "Good" << endl;
        } else {
            cout << "Bad" << endl;
        }
    }
}


void TestA(){

    static const vector<string> in_data {
            "4",
            "ya.ru",
            "maps.me",
            "m.ya.ru",
            "com",
            "7",
            "ya.ru",
            "ya.com",
            "m.maps.me",
            "moscow.m.ya.ru",
            "maps.com",
            "maps.ru",
            "ya.ya"
    };

    stringstream iss;
    for (const string& s: in_data){
        iss << s << '\n';
    }

    vector<string> banned_domains = ReadDomains(iss);
    vector<string> domains_to_check = ReadDomains(iss);


    CheckedDomainStatus(domains_to_check, banned_domains);
};

int main() {

   const vector<string> banned_domains = ReadDomains(cin);
   const vector<string> domains_to_check = ReadDomains(cin);

  CheckedDomainStatus(domains_to_check, banned_domains);
  return 0;
}
//
//4
//ya.ru
//maps.me
//m.ya.ru
//com
//7
//ya.ru
//ya.com
//m.maps.me
//moscow.m.ya.ru
//maps.com
//maps.ru
//ya.ya
//
//

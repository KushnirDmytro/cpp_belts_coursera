#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;


bool IsSubdomain(string_view subdomain, string_view domain) {
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
    for (const string_view domain : domains_to_check) {
        if (const auto it = upper_bound(begin(banned_domains), end(banned_domains), domain);
                it != begin(banned_domains) && IsSubdomain(domain, *prev(it))) {
            cout << "Good" << endl;
        } else {
            cout << "Bad" << endl;
        }
    }
}


int main() {

    vector<string> in_data {
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

  for (string& domain : banned_domains) {
    reverse(begin(domain), end(domain));  // WHY???
    cout << domain << endl;
  }
  sort(begin(banned_domains), end(banned_domains));
  for (const auto& d : banned_domains){
      cout << d << endl;
  }

  size_t insert_pos = 0;
  for ( string& domain : banned_domains) {
    if (insert_pos == 0 || !IsSubdomain(domain, banned_domains[insert_pos - 1])) {
        domain.swap(banned_domains[insert_pos++]);
    }
  }
    for (const auto& d : banned_domains){
        cout << d << endl;
    }
  banned_domains.resize(insert_pos);
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

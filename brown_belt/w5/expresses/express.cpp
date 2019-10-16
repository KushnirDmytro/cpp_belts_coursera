#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "test_runner.h"

using namespace std;

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }

  optional<int> GetClosestReachableTo(const set<int>& reachable, int dest) const {
      bool present = reachable.find(dest) != reachable.end();
      if (present){
          return 0;
      }
       auto upper_closest = reachable.upper_bound(dest);

       auto lower_closest = reachable.lower_bound(dest);
       bool under_lower_exist = lower_closest != reachable.begin();
       if (under_lower_exist) {
           --lower_closest;
       }

      optional<int> res {nullopt};

      if (upper_closest != reachable.end() && lower_closest != reachable.end()) {
          res =  min(abs (dest - *lower_closest) , abs (dest - *upper_closest) );
      } else if (upper_closest == reachable.end() && lower_closest != reachable.end()) {
          res =  abs(dest - *lower_closest);
      } else if (upper_closest != reachable.end() && lower_closest == reachable.end()) {
          res = abs (dest - *upper_closest);
      }
      return res;
  }

  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {
        return result;
    }
    const set<int>& reachable_stations = reachable_lists_.at(start);
    if (!reachable_stations.empty()) {
        if (
                optional<int>
                        closest_to_finish {GetClosestReachableTo(reachable_stations ,finish)};
                closest_to_finish) {
            result = min(result, closest_to_finish.value());
        }
    }
    return result;
  }

private:
  map<int, set<int>> reachable_lists_;
};


void RunRouteManager(istream& is, ostream& os){
    RouteManager routes;

    int query_count;
    is >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        is >> query_type;
        int start, finish;
        is >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            os << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

}


void TestExpresses(){
    vector<string> queries {
            "7\n",
            "ADD -2 5\n",
            "ADD 10 4\n",
            "ADD 5 8\n",
            "GO 4 10\n",
            "GO 4 -2\n",
            "GO 5 0\n",
            "GO 5 100\n"
    };
    vector<int> expected {
            0,
            6,
            2,
            92
    };

    stringstream is;
    for (const auto& q: queries){
        is << q;
    }
    stringstream expected_s;
    for (const auto& er: expected){
        expected_s << er << '\n';
    }

    stringstream os;
    RunRouteManager(is, os);
    int distance;
    for (const auto& d: expected){
        os >> distance;
        ASSERT_EQUAL(d, distance);
    }
}



int main() {
    TestRunner tr;
    RUN_TEST(tr, TestExpresses);

    RunRouteManager(cin, cout);

  return 0;
}

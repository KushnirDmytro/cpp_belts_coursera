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
    reachable_lists_[start].push_back(finish);
    reachable_lists_[finish].push_back(start);
  }


  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {
        return result;
    }
    const vector<int>& reachable_stations = reachable_lists_.at(start);
    if (!reachable_stations.empty()) {
      result = min(
          result,
          abs(finish - *min_element(
              begin(reachable_stations), end(reachable_stations),
              [finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }
          ))
      );
    }
    return result;
  }

private:
  map<int, vector<int>> reachable_lists_;
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
        cout << distance << " : " << d << endl;
        ASSERT_EQUAL(d, distance);
    }
}



int main() {
    TestRunner tr;
    RUN_TEST(tr, TestExpresses);

    RunRouteManager(cin, cout);

  return 0;
}

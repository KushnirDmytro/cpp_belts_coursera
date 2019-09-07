#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    reachable_sets_[start].insert(finish);
    reachable_sets_[finish].insert(start);
  }

  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    const auto &reachable = reachable_sets_.find(start);
    if (reachable == reachable_sets_.end()) {
        return result;
    }

    const set<int> &reachable_stations = reachable->second;

    auto iter_on_closest = reachable_stations.lower_bound(finish);


    if (iter_on_closest == reachable_stations.begin()){
        return min( abs(finish - *iter_on_closest) , result);
    } else if (iter_on_closest == reachable_stations.end()) {
        return min(result, abs(*prev(iter_on_closest) - finish));
    } else {  // upper_b neither begin nor end of set

        return min(
                min(
                        abs(*iter_on_closest - finish),
                        abs(*prev(iter_on_closest) - finish) ),
                        result
                );
    }
  }

private:
  map<int, set<int>> reachable_sets_;
};


int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}

/*
7
ADD -2 5
ADD 10 4
ADD 5 8
GO 4 10
GO 4 -2
GO 5 0
GO 5 100

0
6
2
92
 */

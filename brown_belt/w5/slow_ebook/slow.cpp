#include <iomanip>
#include <iostream>
#include <vector>
#include <test_runner.h>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
  : users_up_to_page{0},
  user_positions{0}
  {}

  void Read(const int user_id, const int page_count) {
      const int old_user_position = user_positions[user_id];
      for (auto pos = next(users_up_to_page.begin(), old_user_position + 1) ;
              pos != next(users_up_to_page.begin(), page_count + 1) && pos != users_up_to_page.end() ;
              ++pos)
      {
          ++(*pos);
      }
      user_positions[user_id] = page_count;
  }

  double Cheer(int user_id) const {

      int current_page = user_positions[user_id];
      if (current_page == 0)
          return 0;
      int users_at_current_page = users_up_to_page [current_page];
      const int same_progress_as_user{users_at_current_page};
      if (users_at_current_page == 1 && users_up_to_page[1] == 1)
          return 1;  // only one
      if (users_at_current_page == users_up_to_page[1])
          return 0;  // no readers have the less progress
      else {
          return (1.0 * users_up_to_page[1] - same_progress_as_user) / (users_up_to_page[1] - 1);
      }

  }

private:
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1000;

  array<int, MAX_PAGE_COUNT_+1> users_up_to_page {0};  // init with zeroes
  array<int, MAX_USER_COUNT_+1> user_positions {0}; // position of each user on book

};


void RunReadingManager(istream& is, ostream& os){

    ReadingManager manager;

    int query_count;
    is >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        is >> query_type;
        int user_id;
        is >> user_id;

        if (query_type == "READ") {
            int page_count;
            is >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            os << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
}



void test_book_usage(){
    const vector<string> queries{
            "12\n"
            "CHEER 5\n"
            "READ 1 10\n"
            "CHEER 1\n"
            "READ 2 5\n"
            "READ 3 7\n"
            "CHEER 2\n"
            "CHEER 3\n"
            "READ 3 10\n"
            "CHEER 3\n"
            "READ 3 11\n"
            "CHEER 3\n"
            "CHEER 1\n"
    };
    const vector<double> expected_results{
            0,
            1,
            0,
            0.5,
            0.5,
            1,
            0.5
    };

    stringstream is;
    for (const auto& q: queries){
        is << q;
    }
    stringstream expected;
    for (const auto& er: expected_results){
        expected << er << '\n';
    }

    stringstream os;
    RunReadingManager(is, os);
    double number;
    for (const auto& d: expected_results){
        os >> number;
        ASSERT_EQUAL(d, number);
    }
}


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ostringstream os;
  TestRunner tr;
  RUN_TEST(tr, test_book_usage);
  RunReadingManager(cin, cout);
  return 0;
}

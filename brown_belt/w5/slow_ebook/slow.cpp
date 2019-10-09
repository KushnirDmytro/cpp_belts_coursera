#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <test_runner.h>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id] == 0) {
      AddUser(user_id);
    }
    user_page_counts_[user_id] = page_count;
    int& position = user_positions_[user_id];
    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
      SwapUsers(position, position - 1);
    }
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    int position = user_positions_[user_id];
    while (position < user_count &&
      user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
        return 0;
    }
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return (user_count - position) * 1.0 / (user_count - 1);
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
  vector<int> user_positions_; // позиции в векторе sorted_users_

  int GetUserCount() const {
    return sorted_users_.size();
  }
  void AddUser(int user_id) {
    sorted_users_.push_back(user_id);
    user_positions_[user_id] = sorted_users_.size() - 1;
  }
  void SwapUsers(int lhs_position, int rhs_position) {
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }
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

/*
12
CHEER 5
READ 1 10
CHEER 1
READ 2 5
READ 3 7
CHEER 2
CHEER 3
READ 3 10
CHEER 3
READ 3 11
CHEER 3
CHEER 1
 */

/*
 0
1
0
0.5
0.5
1
0.5
 * */
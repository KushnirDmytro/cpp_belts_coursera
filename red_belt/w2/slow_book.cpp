#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;



class ReadingManagerSlow {
public:
    ReadingManagerSlow()
            : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
              users_up_to_some_page(MAX_PAGES_COUNT + 1, 0)
              {

              }


    void Read(const int user_id, const int page_count) {
        auto new_user_page_iter = users_up_to_some_page.begin() + page_count;
        auto old_user_page_iter = users_up_to_some_page.begin();

        if (user_page_counts_[user_id] == 0) {
            ++user_count_;
        } else {
            advance(old_user_page_iter, user_page_counts_[user_id]);
        }

        for (auto &page_usrs = new_user_page_iter; page_usrs > old_user_page_iter; --page_usrs) {
            ++(*page_usrs);
        }
        user_page_counts_[user_id] = page_count;  // update n_pages
    }

    double Cheer(const int user_id) const {
        if (user_page_counts_[user_id] == 0) {
            return 0;
        } else if (user_count_ == 1) {
            return 1;
        }

        const int page_count = user_page_counts_[user_id];
        const int users_up_to_this_page_including_him = users_up_to_some_page[page_count];

            return static_cast<double>(user_count_ - users_up_to_this_page_including_him) / (user_count_ - 1);
    }

private:
    // Статическое поле не принадлежит какому-то конкретному
    // объекту класса. По сути это глобальная переменная,
    // в данном случае константная.
    // Будь она публичной, к ней можно было бы обратиться снаружи
    // следующим образом: ReadingManager::MAX_USER_COUNT.
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGES_COUNT = 1000;

    vector<int> user_page_counts_;
    vector<int> users_up_to_some_page; // позиции в векторе sorted_users_
    int user_count_{0};

};




int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false); // FIXME
  cin.tie(nullptr);

  ReadingManagerSlow manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

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

 0
1
0
0.5
0.5
1
0.5

 */
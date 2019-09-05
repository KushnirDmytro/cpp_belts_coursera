#include "test_runner.h"

using namespace std;


template <typename T>
class Table{
public:
    Table(const size_t &w, const size_t &h)
    : content(w, vector<T>(h))
    {

    };

    pair<size_t , size_t> Size() const {
        if (content.empty()){
            return {0, 0};
        } else {
            return {content.size(), content.at(0).size()};
        }
    }

    void Resize(const size_t &new_w, const size_t &new_h){
        content.resize(new_w);
        for(auto &line: content){
            line.resize(new_h);
        }
    }

    vector<T>& operator[](const size_t &w){
        return content[w];
    }

    vector<T>& operator[](const size_t &w) const{
        return content.at(w);
    }

private:
    vector<vector<T>> content;
};

// Реализуйте здесь шаблонный класс Table

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}

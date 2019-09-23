#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;

  bool operator==(const Record &other){ return id == other.id; };
};

// Реализуйте этот класс
class Database {
public:
  bool Put(const Record& record);
  const Record* GetById(const string& id) const;
  Record* GetByIdMutable(const string& id);
  bool Erase(const string& id);

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const;

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const;

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const;

private:
    template <typename MMT>
    void EraseMMap(multimap<MMT, Record*> &mmap, pair<MMT, Record*> p);
    using IdIndex = unordered_map<string_view , Record* > ;
    IdIndex idIndex_;
    using TimestampIndex = multimap<int, Record*>;
    TimestampIndex tsIndex_;
    using KarmaIndex = multimap<int, Record*>;
    KarmaIndex karmaIndex_;
    using UserIndex = multimap<string_view, Record*>;
    UserIndex userIndex_;

};

const Record *Database::GetById(const string &id) const {
    static const Record *no_element{nullptr};
    auto iter_to_element = idIndex_.find(id);
    if (iter_to_element == idIndex_.end())
        return no_element;
    else
        return iter_to_element->second;
}

Record *Database::GetByIdMutable(const string &id) {
    static Record *no_element{nullptr};
    auto iter_to_element = idIndex_.find(id);
    if (iter_to_element == idIndex_.end())
        return no_element;
    else
        return iter_to_element->second;
}

bool Database::Put(const Record &record) {
    const Record* el_by_iter = GetById(record.id);
    if (el_by_iter){
        return false;
    } else {
        auto pair = idIndex_.insert({record.id, new Record(record)});
        tsIndex_.insert( {record.timestamp,pair.first->second});
        karmaIndex_.insert( {record.karma,pair.first->second});
        userIndex_.insert( {record.user,pair.first->second});
        return true;
    }
}

bool Database::Erase(const string &id) {
    Record* el_ptr = GetByIdMutable(id);
    if (el_ptr){
        EraseMMap<int>(karmaIndex_,  {el_ptr->karma, el_ptr});
        EraseMMap<int>(tsIndex_,  {el_ptr->timestamp, el_ptr});
        EraseMMap<string_view >(userIndex_,  {el_ptr->user, el_ptr});
        delete el_ptr;
        idIndex_.erase(id);
        return true;
    } else {
        return false;
    }
}

template<typename MMT>
void Database::EraseMMap(multimap<MMT, Record *> &mmap, pair<MMT, Record *> p) {
    auto eq_range = mmap.equal_range(p.first);
    auto it = eq_range.first;
    while(it != eq_range.second){
        if (it->second == p.second){
            mmap.erase(it);
            return;
        }
    }
}

template<typename Callback>
void Database::AllByUser(const string &user, Callback callback) const {
    auto range = userIndex_.equal_range(user);
    for (auto &it = range.first; it != range.second && callback(*it->second); ++it){}
}

template<typename Callback>
void Database::RangeByKarma(int low, int high, Callback callback) const {
    auto ramge_top = karmaIndex_.upper_bound(high);
    for (auto it = karmaIndex_.lower_bound(low);
    it != ramge_top && callback(*it->second); ++it){}
}

template<typename Callback>
void Database::RangeByTimestamp(int low, int high, Callback callback) const {
    auto ramge_top = tsIndex_.upper_bound(high);
    for (auto it = tsIndex_.lower_bound(low);
         it != ramge_top && callback(*it->second); ++it){}
}


void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}

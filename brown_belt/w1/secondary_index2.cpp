#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

//struct RecordListIndexCompare{
//    bool operator()( list<Record>::iterator &lhs,  list<Record>::iterator &rhs) const {
//        return
//        lhs->timestamp < rhs->timestamp &&
//        lhs->karma < rhs->karma &&
//        lhs->id < rhs->id &&
//        lhs->title < rhs->title &&
//        lhs->user < rhs->user;
//    }
//};


// Реализуйте этот класс
class Database {
public:
  bool Put(const Record& record);

  const Record* GetById(const string& id) const;
  list<Record>::const_iterator GetIterById(const string& id) const;

  bool Erase(const string& id){
      const auto & iter_on_element = GetIterById(id);
      if (iter_on_element == storage_.end())
          return false;
      EraseFromMultimap<int>(*iter_on_element, iter_on_element->timestamp, timestamp_index_);
      EraseFromMultimap<int>(*iter_on_element, iter_on_element->karma, karma_index_);
      EraseFromMultimap<string_view>(*iter_on_element, iter_on_element->user, user_index_);
      id_index_.erase(id);
      storage_.erase(iter_on_element);
      return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const{
      RangeOfElementFromMMap<Callback, int>(MakeRange(low, high), timestamp_index_, callback);
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const{
      RangeOfElementFromMMap<Callback, int>(MakeRange(low, high), karma_index_, callback);
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const{
      RangeOfElementFromMMap<Callback, string_view>(vector<string_view >{user}, user_index_, callback);
  }
private:


    template <typename MultimapType>
    void EraseFromMultimap(
            const Record& record,
            MultimapType key,
            multimap<MultimapType, list<Record>::iterator>& mmap
            ){
        const auto& ts_range = mmap.equal_range(key);
        if (ts_range.first != mmap.end()){
            for (auto pair_it = ts_range.first; pair_it != ts_range.second; ++pair_it){
                if (pair_it->second->id == record.id){
                    mmap.erase(pair_it);
                }
            }
        }
  }

    template <typename MultimapType>
    bool RecordIsPointedByRangeOfIters(
            const Record& record,
            const pair<
                    typename multimap<MultimapType, list<Record>::iterator>::iterator,
                    typename multimap<MultimapType, list<Record>::iterator>::iterator> & range){
        return find_if(
                range.first,
                range.second,
                [&record](const auto& iter_in_list)
                { return *(iter_in_list.second) == record;}
        ) == range.second;
    }


    void Insert(const Record &new_record){
        storage_.push_back(new_record);
        auto iter = prev(storage_.end());
        karma_index_.insert({iter->karma, iter});
        timestamp_index_.insert({iter->timestamp, iter});
        user_index_.insert({iter->user, iter});
        id_index_.insert({iter->id, iter});
    }

    template <typename T>
    vector<T> MakeRange(const T &low, const T &hight) const {
        vector<T> res{low};
        auto el = low + 1;
        while (el <= hight){
            res.push_back(el++);
        }
        return res;
    }

    template <typename Callback, typename MMapKeyType>
    void RangeOfElementFromMMap(
            const vector<MMapKeyType> &value_range,
            const multimap<MMapKeyType, list<Record>::iterator> &MMap,
    Callback cb) const {
        for (const auto &key_value : value_range){
            auto range_for_key = MMap.equal_range(key_value);
            if(range_for_key.first != MMap.end()){
                for (auto& it = range_for_key.first; it != range_for_key.second; ++it){
                    if (!cb(*it->second))
                        return;
                }
            }
        }
    }


    list<Record> storage_;

    unordered_map<string_view , list<Record>::iterator> id_index_;
    multimap<int, list<Record>::iterator> karma_index_;
    multimap<int, list<Record>::iterator> timestamp_index_;
    multimap<string_view , list<Record>::iterator> user_index_;
};



bool Database::Put(const Record &record) {
    const auto &it_on_el = GetIterById(record.id);
    if (it_on_el != storage_.end())
        return false;
    else {
        Insert(record);
        return true;
    }
}

const Record *Database::GetById(const string &id) const {
    static const Record *novalue{ nullptr};
    const auto& it_to_el = GetIterById(id);
    if (it_to_el == storage_.end())
        return novalue;
    else
        return &(*it_to_el);
}

  list<Record>::const_iterator Database::GetIterById(const string &id) const{
    const auto& it = id_index_.find(id);
    if(it == id_index_.end()){
        return storage_.end();
    } else {
        return it->second;  // else we cannot access second element of the "end()" iterator
    }
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


void TestNonExisting() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
//    auto record = db.RangeByKarma("id");
//    auto record = db.RangeByTimestamp("id");

    int count = 0;
    db.AllByUser("WOW", [&count](const Record&) {
        ++count;
        return true;
    });
     count = 0;
    db.RangeByKarma(-100, -99, [&count](const Record&) {
        ++count;
        return true;
    });
     count = 0;
    db.RangeByTimestamp(15361072, 15361072, [&count](const Record&) {
        ++count;
        return true;
    });
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;

    RUN_TEST(tr, TestReplacement);
    RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestNonExisting);
  return 0;
}

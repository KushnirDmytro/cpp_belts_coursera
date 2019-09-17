#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <deque>

using namespace std;



template <typename T>
class PriorityCollection {

public:
    using Rank = size_t;
    using UID = size_t;
    struct StoreT {
        T el_;
        Rank rank_;
        const UID uid_;

        StoreT(T el, Rank rank, UID uid)
        : el_{move(el)},
        rank_{rank},
        uid_{uid}
        {

        };

        StoreT (StoreT && move_from)
        : el_{move(move_from.el_)},
        rank_{move_from.rank_},
        uid_{move_from.uid_}
        {

        }
    };
    using Id = typename list<StoreT>::iterator; /* тип, используемый для идентификаторов */;
    struct Id_Compare{
        bool operator()( const Id &lhs, const Id &rhs) const { return lhs->uid_ < rhs->uid_; };
    };


    list<StoreT> data_;
    deque<set<Id, Id_Compare>> ranking_newest_;
    map<Id, UID, Id_Compare> existance_;


    UID uid_{0};


    PriorityCollection()
    : ranking_newest_{{}}
    {

    }


    // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object){
        UID new_uid = uid_++;
        data_.push_back( StoreT(move(object), 0, new_uid) );
        const Id object_location = prev(data_.end());
        ranking_newest_[0].insert(object_location);
        existance_[object_location] = uid_;
        return object_location;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){
        for (ObjInputIt &it = range_begin; it != range_end; ++it){
//            cout << *it << endl;
            *ids_begin = Add(move(*it));
            ++ids_begin;
        }
    };
  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const { return existance_.lower_bound(id) != existance_.end(); }

  // Получить объект по идентификатору
  const T& Get(Id id) const{ return id->el_; }

  // Увеличить приоритет объекта на 1
  void Promote(Id id){
      Rank old_rank = id->rank_++;
      if (old_rank == ranking_newest_.size() - 1){
          ranking_newest_.push_back({});
      }

      ranking_newest_[old_rank].erase(id);
      ranking_newest_[old_rank + 1].insert(id);
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
      const set<Id, Id_Compare> &last_element = GetMaxRankSet();
      const Id& max_elem_id = *prev(last_element.end());
      return {max_elem_id->el_, max_elem_id->rank_};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
      set<Id, Id_Compare> &last_element = GetMaxRankSet();
      auto it_on_last = prev(last_element.end());
      Id last = *it_on_last;
      last_element.erase(it_on_last);
      existance_.erase(last);

      StoreT res = move(*last);

      data_.erase(last);
      return {move(res.el_), res.rank_};
  }

private:
    const set<Id, Id_Compare>& GetMaxRankSet() const {
      auto set_iter = prev(ranking_newest_.end());
      while (set_iter->empty()){
          set_iter = prev(set_iter);
      }
      return *set_iter;
  }
    set<Id, Id_Compare>& GetMaxRankSet(){
        auto set_iter = prev(ranking_newest_.end());
        while (set_iter->empty()){
            set_iter = prev(set_iter);
        }
        return *set_iter;
    }
  // Приватные поля и методы
};



class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
    {
        const auto &item = strings.GetMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}


void TestNoCopyList() {
    PriorityCollection<StringNonCopyable> strings;
    vector<StringNonCopyable> in_strings; // {"white", "yellow", "red"};
    in_strings.emplace_back("white");
    in_strings.emplace_back("yellow");
    in_strings.emplace_back("red");
    using Id = PriorityCollection<StringNonCopyable>::Id;
    vector<Id> ids;
    strings.Add(
            make_move_iterator(in_strings.begin()),
            make_move_iterator(in_strings.end()), back_inserter(ids));
//    cout << "BANG" << endl;
    Id yellow_id = ids[1];
    Id red_id = ids[2];
//
    {
        ASSERT(strings.IsValid(yellow_id));
        ASSERT_EQUAL(strings.Get(yellow_id), "yellow");
    }
    strings.Promote(ids[1]);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto &item = strings.GetMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {

        ASSERT_EQUAL(true, strings.IsValid(red_id));
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
        ASSERT_EQUAL(false, strings.IsValid(red_id));
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  RUN_TEST(tr, TestNoCopyList);
  return 0;
}

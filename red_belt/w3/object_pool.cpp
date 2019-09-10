#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <list>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
      if (deallocated_.empty()){
          allocated_.push_front(new T);
          return allocated_.front();
      } else {
          T* result = deallocated_.front();
          allocated_.push_front(result);
          deallocated_.pop_front();
          return result;
      }
  }

  T* TryAllocate() {
      if (deallocated_.empty()) {
          return nullptr;
      } else {
          return Allocate();
      }
  }


  void Deallocate(T* object){
      auto object_it = find(allocated_.begin(), allocated_.end(), object);
      if (object_it == allocated_.end()){
          throw invalid_argument("attempt to deallocate not allocated object");
      } else {
          deallocated_.push_back(*object_it);
          allocated_.erase(object_it);
      }
  }

  ~ObjectPool(){
      for (T* object : allocated_){
          delete object;
      }
      for (T* object: deallocated_){
          delete object;
      }
  }

public:
  // Добавьте сюда поля
  list<T*> allocated_;
  deque<T*> deallocated_;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}

#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
    T* handle_;
public:

  UniquePtr() : handle_{nullptr} {};
  UniquePtr(T * ptr) : handle_{move(ptr)} {};
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other) : handle_{other.handle_} {other.handle_ = nullptr;};
  UniquePtr& operator = (const UniquePtr&) = delete;
  UniquePtr& operator = (nullptr_t) {
      delete handle_;
      handle_ = nullptr;
      return *this;
  }
  UniquePtr& operator = (UniquePtr&& other) {
      handle_ = move(other.handle_);
      other.handle_ = nullptr;
      return *this;
  }
  ~UniquePtr() { delete handle_; }

  T& operator * () const { return *handle_ ; }

  T * operator -> () const { return handle_; }

  T * Release() {
      T* tmp = handle_;
      handle_ = nullptr;
      return tmp;
  }

  void Reset(T * ptr){
      if (handle_ && ptr != handle_)
          delete handle_;
      handle_ = ptr;
  }

  void Swap(UniquePtr& other) {
      if (other.handle_ != handle_){
          T* tmp = move(other.handle_);
          other.handle_ = move(handle_);
          handle_ = move(tmp);
      }
  }

  T * Get() const { return handle_; }
};


struct Item {
  static int counter;
  int value;
  Item(int v = 0): value(v) {
    ++counter;
  }
  Item(const Item& other): value(other.value) {
    ++counter;
  }
  ~Item() {
    --counter;
  }
};

int Item::counter = 0;


void TestLifetime() {
  Item::counter = 0;
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    ptr.Reset(new Item);
    ASSERT_EQUAL(Item::counter, 1);
  }
  ASSERT_EQUAL(Item::counter, 0);

  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    auto rawPtr = ptr.Release();
    ASSERT_EQUAL(Item::counter, 1);

    delete rawPtr;
    ASSERT_EQUAL(Item::counter, 0);
  }
  ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
  UniquePtr<Item> ptr(new Item(42));
  ASSERT_EQUAL(ptr.Get()->value, 42);
  ASSERT_EQUAL((*ptr).value, 42);
  ASSERT_EQUAL(ptr->value, 42);
}

void TestSwap() {
    UniquePtr<Item> ptr1(new Item(41));
    UniquePtr<Item> ptr2(new Item(42));
    ptr1.Swap(ptr2);
    ASSERT_EQUAL(ptr1.Get()->value, 42);
    ASSERT_EQUAL(ptr2.Get()->value, 41);
    ptr1.Swap(ptr1);
    ASSERT_EQUAL(ptr1.Get()->value, 42);

}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLifetime);
  RUN_TEST(tr, TestGetters);
  RUN_TEST(tr, TestSwap);
}

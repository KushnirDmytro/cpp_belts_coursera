#include "test_runner.h"

#include <functional>
#include <string>
#include <memory>
using namespace std;

template <typename T>
class LazyValue {
public:
  explicit LazyValue(std::function<T()> init)
  : element_ptr{nullptr},
  init_{init}
  {

  }

  bool HasValue() const{
      return element_ptr != nullptr;
  }

  const T& Get() const{
      if (!HasValue())
          element_ptr = make_shared<T>(init_());
      return *element_ptr;
  }

private:
    mutable  shared_ptr<T> element_ptr;
    std::function<T()> init_;
};

void UseExample() {
  const string big_string = "Giant amounts of memory";

  LazyValue<string> lazy_string([&big_string] { return big_string; });

  ASSERT(!lazy_string.HasValue());
  ASSERT_EQUAL(lazy_string.Get(), big_string);
  ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
  bool called = false;

  {
    LazyValue<int> lazy_int([&called] {
      called = true;
      return 0;
    });
  }
  ASSERT(!called);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, UseExample);
  RUN_TEST(tr, TestInitializerIsntCalled);
  return 0;
}

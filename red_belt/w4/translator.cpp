#include "test_runner.h"
#include <string>
#include <vector>
#include <string_view>

using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target){
      auto iter_in_src = known_src.insert(string(source));
      auto iter_in_target = known_trgt.insert(string(target));
      src_trgt[string_view (*iter_in_src.first)] = string_view(*iter_in_target.first);
      trgt_src[string_view (*iter_in_target.first)] = string_view(*iter_in_src.first);
  }
  string_view TranslateForward(string_view source) const {
      auto trgt_it = src_trgt.find(source);
      if (trgt_it == src_trgt.end()){
          return "";
      } else {
          return trgt_it->second;
      }
  }

  string_view TranslateBackward(string_view target) const{
      auto strc_it = trgt_src.find(target);
      if (strc_it == trgt_src.end()){
          return "";
      } else {
          return strc_it->second;
      }
  }

private:
  set<string> known_src;
  set<string> known_trgt;
  map<string_view, string_view> src_trgt;
  map<string_view, string_view> trgt_src;
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}

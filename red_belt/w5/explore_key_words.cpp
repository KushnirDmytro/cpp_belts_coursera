#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other){
      for (const auto& pair: other.word_frequences){
          word_frequences[pair.first] += pair.second;
      }
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    stringstream line_stream (line);
    string buf;
    Stats st;
    while(line_stream >> buf){
        if (key_words.find(buf) != key_words.end())
            ++st.word_frequences[buf];
    }
    return st;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input, mutex &mt
) {
  Stats result;
  string line_buf;
  while(true){
      {
          lock_guard<mutex> lock(mt);
          if (!getline(input, line_buf))
              break;
      }
      result += ExploreLine(key_words, line_buf);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<future<Stats>> v;
    mutex mt;
    size_t n_threads {4};
    for (size_t i{0}; i < n_threads; ++i){
        v.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(input), ref(mt)) );
    }
    Stats sum;
    for ( auto& el: v){
        sum += el.get();
    }
    return sum;
  // Реализуйте эту функцию
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}

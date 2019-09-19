#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <future>
#include <deque>
#include <unordered_map>
using namespace std;

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) : value{move(initial)}
    {

    }

    struct Access {
        Access(T& ref_to, mutex &mt)
                :
                lock(mt),
                ref_to_value {ref_to}
        {

        }
        lock_guard<mutex> lock;
        T& ref_to_value;
    };

    Access GetAccess(){
        return Access(value, mt_);
    }
private:
    mutex mt_;
    T value;
};

class InvertedIndex {
public:
  void Add(string document);
  const vector<pair<size_t , size_t >>& Lookup(string_view word) const;

//  const vector<string>& GetDocuments() const {
//      return docs;
//  }

    deque<string> docs;
private:
    unordered_map<string_view , unordered_map<size_t, size_t >> index;  // word to document ID
    unordered_map<string_view, vector<pair<size_t, size_t >> > word_to_ready_result;

};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    void AddQueriesStreamAsync(istream& query_input, ostream& search_results_output);
    void UpdateDocumentBaseAsync(istream& document_input);
    Synchronized<InvertedIndex> sync_index;
  deque<future<void>> async_calls;
};

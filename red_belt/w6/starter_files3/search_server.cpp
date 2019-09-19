#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>


void LeftStrip(string_view& sv) {
    while (!sv.empty() && isspace(sv[0])) {
        sv.remove_prefix(1);
    }
}

string_view ReadToken(string_view& sv) {
    LeftStrip(sv);

    auto pos = sv.find(' ');
    auto result = sv.substr(0, pos);
    sv.remove_prefix(pos != sv.npos ? pos : sv.size());
    return result;
}

vector<string_view> SplitIntoWordsView(string_view str) {
    vector<string_view> result;

    for (string_view word = ReadToken(str); !word.empty(); word = ReadToken(str)) {
        result.push_back(word);
    }

    return result;
}


vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

vector<string_view> SplitIntoStringView( const string& line ){
//    vector<string_view> v;
    string_view buf (line);
    vector<string_view > vec = SplitBy(Strip(buf), ' ');
    return vec;
}

SearchServer::SearchServer(istream& document_input) {
    UpdateDocumentBaseAsync(document_input);
}

void SearchServer::UpdateDocumentBaseAsync(istream& document_input) {
  InvertedIndex new_index;
  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  swap(sync_index.GetAccess().ref_to_value, new_index);
}



void SearchServer::UpdateDocumentBase(istream& document_input){
    async_calls.push_back(
            async(
//                    launch::async,
                    &SearchServer::UpdateDocumentBaseAsync,
                    this,
                    ref(document_input)
            )
    );

}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output){
    async_calls.push_back(
            async(
//                    launch::async,
                    &SearchServer::AddQueriesStreamAsync,
                    this,
                    ref(query_input),
                    ref(search_results_output))
            );
}

void SearchServer::AddQueriesStreamAsync(istream &query_input, ostream &search_results_output) {

    vector<pair<size_t, int64_t >> search_results;
    pair<size_t , size_t > p{0u,0u};
    search_results.reserve(sync_index.GetAccess().ref_to_value.docs.size());

    for (string current_query; getline(query_input, current_query); ) {

    const auto &words = SplitIntoWordsView(current_query);

    {
        const auto &access = sync_index.GetAccess();
        search_results.assign(access.ref_to_value.docs.size(), p);

        for (const auto& word : words) {
            for (const auto &[docid, docid_count] : access.ref_to_value.Lookup(word)) {
                search_results[docid].first += docid_count;
                search_results[docid].second = -docid;
            }
        }
    }


    partial_sort(
      begin(search_results),
      search_results.size() >= 5 ? begin(search_results) + 5:  end(search_results),
      end(search_results),
      []( const auto &lhs, const auto &rhs) {
        return lhs > rhs;
      }
    );

    search_results_output << current_query << ':';
    for (auto [hitcount, docid] : Head(search_results, 5)) {
        if (hitcount)
      search_results_output << " {"
        << "docid: " << -docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }


}

void InvertedIndex::Add(string document) {
  docs.push_back(move(document));
    unordered_map<size_t ,size_t>::iterator entry_iter;

  const size_t docid = docs.size() - 1;

  for (const auto& word : SplitIntoWordsView(docs.back())) {
      auto index_to_word_iter = index.find(word);
      if (index_to_word_iter == index.end()){
          auto pair = index.insert({word, {}});
          index_to_word_iter = pair.first;
      }
      entry_iter = index_to_word_iter->second.find(docid);
      if (entry_iter == index_to_word_iter->second.end()){
          auto &vector_content = word_to_ready_result[word];
          index_to_word_iter->second.insert({docid, vector_content.size()});
          vector_content.emplace_back(docid, 1);
      } else  {
          ++word_to_ready_result[word][entry_iter->second].second;
      }

  }
}


// has to return vector of ready pairs
const vector<pair<size_t , size_t>>& InvertedIndex::Lookup(string_view  word) const {
    static const vector<pair<size_t , size_t >> none;
  if (auto it = word_to_ready_result.find(word); it != word_to_ready_result.end()) {
      return it->second;
  } else {
    return none;
  }
}

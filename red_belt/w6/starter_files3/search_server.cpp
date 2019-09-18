#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
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
                    launch::async,
                    &SearchServer::UpdateDocumentBaseAsync,
                    this,
                    ref(document_input)
            )
    );

}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output){
//    AddQueriesStreamAsync(query_input, search_results_output);
    async_calls.push_back(
            async(
                    launch::async,
                    &SearchServer::AddQueriesStreamAsync,
                    this,
                    ref(query_input),
                    ref(search_results_output))
            );

}

void SearchServer::AddQueriesStreamAsync(istream &query_input, ostream &search_results_output) {

    vector<pair<size_t, int64_t >> search_results;
    search_results.reserve(sync_index.GetAccess().ref_to_value.docs.size());

    for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);

      search_results.assign(sync_index.GetAccess().ref_to_value.docs.size(), {0,0});
    for (const auto& word : words) {
      for (const auto &[docid, docid_count] : sync_index.GetAccess().ref_to_value.Lookup(word)) {
          search_results[docid].first += docid_count;
          search_results[docid].second = -docid;
      }
    }

    search_results.erase(
            remove_if(search_results.begin(),
                    search_results.end(),
                    [](auto &el){ return el.first == 0;}),
                    search_results.end());

    partial_sort(
      begin(search_results),
      search_results.size() >= 5 ? begin(search_results) + 5:  end(search_results),
      end(search_results),
      []( auto lhs,  auto rhs) {
        return lhs > rhs;
      }
    );

    search_results_output << current_query << ':';
    for (auto [hitcount, docid] : Head(search_results, 5)) {
      search_results_output << " {"
        << "docid: " << -docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }


}

void InvertedIndex::Add(const string& document) {
  docs.push_back(document);

  const size_t docid = docs.size() - 1;

  for (const auto& word : SplitIntoWords(document)) {
      if (index[word].find(docid) == index[word].end()) {
          index[word][docid] = word_to_ready_result[word].size();  //new position of a word
          word_to_ready_result[word].emplace_back(docid, 1);
      } else  {
          ++word_to_ready_result[word][index[word][docid]].second;
      }

  }
}


// has to return vector of ready pairs
const vector<pair<size_t , size_t>>& InvertedIndex::Lookup(const string& word) const {
    static const vector<pair<size_t , size_t >> none;
  if (auto it = word_to_ready_result.find(word); it != word_to_ready_result.end()) {
      return it->second;
  } else {
    return none;
  }
}

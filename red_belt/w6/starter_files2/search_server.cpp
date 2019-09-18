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
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
    vector<pair<size_t, int64_t >> search_results;
    search_results.reserve(index.docs.size());

    for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);

      search_results.assign(index.docs.size(), {0,0});
    for (const auto& word : words) {
      for (const auto &[docid, docid_count] : index.Lookup(word)) {
          search_results[docid].first += docid_count;
          search_results[docid].second = -docid;
      }
    }

    search_results.erase(
            remove_if(search_results.begin(),
                    search_results.end(),
                    [](auto &el){ return el.first == 0;}),
                    search_results.end());

//    erase(remove(search_results.begin(), search_results.end(), [](const pair<size_t, size_t> &el){ return el.second == 0;}), search_results.end());

//    vector<pair<size_t, size_t>> search_results = (
//      docid_count.begin(), docid_count.end()
//    );
    partial_sort(
      begin(search_results),
      search_results.size() >= 5 ? begin(search_results) + 5:  end(search_results),
      end(search_results),
      [](const auto& lhs, const auto& rhs) {
//        int64_t lhs_docid = lhs.first;
//        auto lhs_hit_count = lhs.second;
//        int64_t rhs_docid = rhs.first;
//        auto rhs_hit_count = rhs.second;
        return lhs > rhs;
//        return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
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
//      size_t old_id_in_docindex = index[word][docid]++;
      if (index[word].find(docid) == index[word].end()) {
          index[word][docid] = word_to_ready_result[word].size();  //new position of a word
          word_to_ready_result[word].emplace_back(docid, 1);
      } else  {
          ++word_to_ready_result[word][index[word][docid]].second;
      }

//    .push_back(docid);

  }
}


// has to return vector of ready pairs
vector<pair<size_t , size_t>> InvertedIndex::Lookup(const string& word) const {
  if (auto it = word_to_ready_result.find(word); it != word_to_ready_result.end()) {
      return it->second;
//    return it->second;
  } else {
    return {};
  }
}

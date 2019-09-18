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

  sync_index.GetAccess().ref_to_value = move(new_index);
//  index = move(new_index);

//    cout << "Async update documents update finished" << endl;
}


void SearchServer::UpdateDocumentBlocking(istream& document_input) {
    auto acc = sync_index.GetAccess();

    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document); ) {
        new_index.Add(move(current_document));
    }

    acc.ref_to_value = move(new_index);

//    cout << "Sync update documents update finished" << endl;
}

void SearchServer::UpdateDocumentBase(istream& document_input){
//    if (sync_index.GetAccess().ref_to_value.docs.empty()) {
//        auto acc = sync_index.GetAccess();
//        InvertedIndex new_index;
//        for (string current_document; getline(document_input, current_document); ) {
//            new_index.Add(move(current_document));
//        }
//        acc.ref_to_value = move(new_index);

//        async_calls.push_back(
//                async(
//                        launch::async,
//                        &SearchServer::UpdateDocumentBlocking,
//                        this,
//                        ref(document_input)
//                )
//        );
//    } else {
//        async_calls.push_back(
//                async(
//                        launch::async,
//                        &SearchServer::UpdateDocumentBaseAsync,
//                        this,
//                        ref(document_input)
//                )
//        );
//    }
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output){
//    this_thread::sleep_for(chrono::microseconds(1000000));
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
//    this_thread::sleep_for(chrono::microseconds(1000));
//    cout << "Async  query processing started :" << sync_index.GetAccess().ref_to_value.docs.size() << endl;
    vector<pair<size_t, int64_t >> search_results;
    pair<size_t, int64_t > p = {0u, 0};
    search_results.reserve(sync_index.GetAccess().ref_to_value.docs.size());

    for (string current_query; getline(query_input, current_query); ) {

    const auto words = SplitIntoWords(current_query);

      search_results.assign(sync_index.GetAccess().ref_to_value.docs.size(), p);
    for (const auto& word : words) {
      for (const auto &[docid, docid_count] : sync_index.GetAccess().ref_to_value.Lookup(word)) {
          search_results[docid].first += docid_count;
          search_results[docid].second = -docid;
      }
    }

//    search_results.erase(
//            remove_if(search_results.begin(),
//                    search_results.end(),
//                    [](auto &el){ return el.first == 0;}),
//                    search_results.end());


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
        if (hitcount)
      search_results_output << " {"
        << "docid: " << -docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }

//    cout << "Async  query processing finished :" << sync_index.GetAccess().ref_to_value.docs.size() << endl;

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
  } else {
    return {};
  }
}

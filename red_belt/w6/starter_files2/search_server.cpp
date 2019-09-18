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

  swap(sync_index.GetAccess().ref_to_value , new_index);
}


void SearchServer::UpdateDocumentBlocking(istream& document_input) {
    auto acc = sync_index.GetAccess();

    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document); ) {
        new_index.Add(move(current_document));
    }

    acc.ref_to_value = move(new_index);
}

void SearchServer::UpdateDocumentBase(istream& document_input){

//    if (sync_index.GetAccess().ref_to_value.docs.empty()) {
//        auto acc = sync_index.GetAccess();
//        InvertedIndex new_index;
//        for (string current_document; getline(document_input, current_document); ) {
//            new_index.Add(move(current_document));
//        }
//        acc.ref_to_value = move(new_index);
//    }
//    else {
        async_calls.push_back(
                async(
                        launch::async,
                        &SearchServer::UpdateDocumentBaseAsync,
                        this,
                        ref(document_input)
                )
        );
//    }
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output){
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
    pair<size_t, int64_t > p = {0u, 0};

    size_t WordsNumberInDocs = sync_index.GetAccess().ref_to_value.docs.size();
    search_results.reserve(WordsNumberInDocs);

    for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);

      search_results.assign(WordsNumberInDocs, p);
    for (const auto& word : words) {
            for (const auto &[docid, docid_count] :  sync_index.GetAccess().ref_to_value.Lookup(word)) {
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

}

void InvertedIndex::Add( const string &document) {
  docs.push_back(document);

  const size_t docid = docs.size() - 1;

    for (const auto& word : SplitIntoWords(document)) {
       auto it_on_word_in_map = index.find(word);

        map<string, vector <pair <size_t, size_t > >>::iterator vec_iter;

        if (it_on_word_in_map == index.end()){ // nullptr case
           auto iter_on_new_element = index.insert({word,{}});
           it_on_word_in_map = iter_on_new_element.first;
            vec_iter = word_to_ready_result.insert({word, {}}).first;

       } else {
            vec_iter = word_to_ready_result.find(word);
       }

      if (auto it = it_on_word_in_map->second.find(docid); it == it_on_word_in_map->second.end()) {
          it_on_word_in_map->second[docid] = vec_iter->second.size();  //new position of a word
          vec_iter->second.emplace_back(docid, 1);
      } else  {
          ++(vec_iter->second)[it->second].second;
      }

  }
}


// has to return vector of ready pairs
const vector<pair<size_t , size_t>>& InvertedIndex::Lookup(const string& word) const {
    static const vector<pair<size_t , size_t>> empty;
  if (auto it = word_to_ready_result.find(word); it != word_to_ready_result.end()) {
      return it->second;
  } else {
    return empty;
  }
}

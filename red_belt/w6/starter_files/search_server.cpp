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
//        , AllDurations* all_durs = nullptr
) {


    for (string current_query; getline(query_input, current_query); ) {
        // READING WORDS
//        vector<string> words;
//        {
//            ADD_DURATION(*all_durs->reading_time);
            const auto  words = SplitIntoWords(current_query);
//        }


        // MAKING LOOKUP
//        map<size_t, size_t> docid_count;

//        vector<size_t> docid_count(index.GetNdocs());

//        docid_count.reserve(index.GetNdocs());
//        {
//            ADD_DURATION(*all_durs->making_index_time);
//            for (const auto& word : words) {
//                for (const size_t docid : index.Lookup(word)) {
//                    docid_count[docid]++;
//                }
//            }
//        }
//        for (int i = 0; i < docid_count.size(); ++i){
//            cout << i << ":" << docid_count[i] << endl;
//        }
//        cout << endl;

//        vector<pair<size_t, size_t >> search_results{
//            begin(docid_count), end(docid_count)
//        };
//        search_results.reserve(index.GetNdocs());
//        for (size_t i{0}; i < index.GetNdocs(); ++i){
//            search_results[i] = {docid_count[i], i};
//        }


//        cout << "Search results with map" << endl;

//        cout << "Search results with map size " << search_results.size() << endl;
//        cout << "Docid results with map size " << docid_count.size() << endl;
//        cout << "NDOCS results with map size " << index.GetNdocs() << endl;
//        for (const auto& [a, b]: search_results){
//            cout << a << ":" << b << endl;
//        } cout << endl;


        vector<size_t> docid_count_vector(index.GetNdocs()); // require zeros init
//        (index.GetNdocs());

//        docid_count_vector.resize;
//        {
//            ADD_DURATION(*all_durs->making_index_time);
            for (const auto& word : words) {
                for (const size_t docid : index.Lookup(word)) {
                    ++docid_count_vector[docid];
                }
            }
//        }
//        for (int i = 0; i < docid_count_vector.size(); ++i){
//            cout << i << ":" << docid_count_vector[i] << endl;
//        }
//        cout << endl;

        vector<pair<size_t, size_t >> search_results;
        search_results.reserve(index.GetNdocs());
        for (size_t i{0}; i < index.GetNdocs(); ++i){
            if (docid_count_vector[i])
                search_results.emplace_back(i, docid_count_vector[i]);
//            search_results[i] = {docid_count_vector[i], i};
        }

//        cout << "Search results with vector size " << search_results.size() << endl;
//        cout << "Docid results with vector size " << docid_count_vector.size() << endl;
//        cout << "NDOCS results with vector size " << index.GetNdocs() << endl;
//        for (const auto& [a, b]: search_results){
//            cout << a << ":" << b << endl;
//        } cout << endl;

//        vector<pair<size_t, size_t >> search_results(
//                docid_count.begin(), docid_count.end()
//        );

        // TOTAL SORTING
//        {
//            ADD_DURATION(*all_durs->sorting_time);

            partial_sort(
                    begin(search_results),
                    search_results.size() > 5? begin(search_results) + 5: end(search_results) ,
                    end(search_results),
                    [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
//          return lhs.second < rhs.second;
                        int64_t lhs_docid = lhs.first;
                        auto lhs_hit_count = lhs.second;
                        int64_t rhs_docid = rhs.first;
                        auto rhs_hit_count = rhs.second;
                        return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
                    }
            );
//        }

        // Forming output
//        {
//            ADD_DURATION(*all_durs->printing_time);
            search_results_output << current_query << ':';
            for (auto[docid, hitcount] : Head(search_results, 5)) {
                search_results_output << " {"
                                      << "docid: " << docid << ", "
                                      << "hitcount: " << hitcount << '}';
            }
            search_results_output << endl;
//        }
    }
}

void InvertedIndex::Add(const string& document) {
  docs.push_back(document);

  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(document)) {
    index[word].push_back(docid);
  }
}

list<size_t> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}

#include "Common.h"

#include <unordered_map>
#include <string>
#include <list>
#include <memory>
#include <mutex>
#include <iostream>

using namespace std;

class LruCache : public ICache {

    struct Cache{
    private:
        unordered_map<string, list<BookPtr>::iterator> index_;
        list<BookPtr> storage_;
        mutex mt_;
        size_t stored_bytes_{0};
    public:

        const size_t max_stored_;

        Cache(size_t max_stored) : max_stored_{max_stored} {};

        struct Access{
            unordered_map<string, list<BookPtr>::iterator>& index;
            list<BookPtr>& storage_;
            size_t & stored_bytes_;
            const lock_guard<mutex> lock_;
        };

        Access GetAccess(){
            return {index_,
                    storage_,
                    stored_bytes_,
                    lock_guard<mutex>(mt_)};
        }
    };

    void PopLRUBook(Cache::Access& cache_handle){
        auto LRU_book_iter = cache_handle.storage_.begin();
        cache_handle.index.erase(LRU_book_iter->get()->GetName());
        cache_handle.stored_bytes_ -= LRU_book_iter->get()->GetContent().size();
        cache_handle.storage_.erase(LRU_book_iter);
    }

    pair<BookPtr, bool> PushBackBook(const BookPtr &book, Cache::Access& cache_handle) {
        cache_handle.storage_.push_back(book);
        auto book_storage_it = prev(cache_handle.storage_.end());
        cache_handle.stored_bytes_ += book_storage_it->get()->GetContent().size();
        cache_handle.index[book_storage_it->get()->GetName()] = book_storage_it;

        while (cache_handle.stored_bytes_ > cache_.max_stored_ )
            PopLRUBook(cache_handle);
        if (cache_handle.storage_.empty()){
            return {nullptr, false};
        } else {
            return {*book_storage_it, true};
        }
    }


        static void UpdateRating(list<BookPtr>::iterator& it, Cache::Access& cache_handle) {
            cache_handle.storage_.splice(cache_handle.storage_.end(), cache_handle.storage_, it);
        }

        public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker,
      const Settings& settings
  ):
  cache_{settings.max_memory},
  archive_{move(books_unpacker)}
  {

  }





  BookPtr GetBook(const string& book_name) override {

      Cache::Access acc = cache_.GetAccess();

      auto it = acc.index.find(book_name);
      bool is_in_cache = it != acc.index.end();

      if (! is_in_cache){

          // TODO check if is not too time consuming
          BookPtr unpacked_book_ = archive_->UnpackBook(book_name);
          size_t unpacked_book_size = unpacked_book_->GetContent().size();

          while ( !acc.storage_.empty() &&
                  acc.stored_bytes_ + unpacked_book_size > cache_.max_stored_ ) {
              PopLRUBook(acc);
          }

          auto cached = PushBackBook(unpacked_book_, acc);
          return cached.second ? cached.first : unpacked_book_;
      } else {
          UpdateRating(it->second, acc);
          return *it->second;
      }
  }

private:
  Cache cache_;
  shared_ptr<IBooksUnpacker> archive_;
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
    return make_unique<LruCache>(move(books_unpacker), settings);
}

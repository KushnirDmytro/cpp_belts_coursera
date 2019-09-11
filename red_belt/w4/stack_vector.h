#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0){
      if ( a_size > Capacity() ){
          throw invalid_argument("Constructor argument is bigger then max capacity");
      }
      size_ = a_size;
  }

  T& operator[](size_t index) { return *(begin() + index); }
  const T& operator[](size_t index) const { return *(begin() + index); }

  auto begin() { return ar_.begin(); }
  auto end() { return ar_.begin() + size_; };
  auto begin() const { return ar_.begin(); } ;
  auto end() const { return ar_.begin() + size_; };

  size_t Size() const { return size_; }
  size_t Capacity() const { return ar_.size(); }

  void PushBack(const T& value) {
      if (Size() >= Capacity()){
          throw overflow_error("PushBack to full StackVector");
      } else {
          *end() = value;
          ++size_;
      }
  }

  T PopBack(){
      if (Size() == 0){
          throw underflow_error("Poping from empty StackVector");
      } else {
//          T last_element = *(end() - 1);
          --size_;
          return *(end());
      }
  }

private:
    array<T, N> ar_;
    size_t size_;
};


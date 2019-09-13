#include <cstdint>
#include <algorithm>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
  SimpleVector();
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);
  void PushBack(T&& value);
  void Resize(size_t desired_size);

  // При необходимости перегрузите
  // существующие публичные методы

private:
    T* data_;
    T* end_;
    size_t capacity_;
  // Добавьте сюда поля
};


template<typename T>
SimpleVector<T>::SimpleVector()
        :
        data_{nullptr},
        end_{nullptr},
        capacity_{0}
{

}


template<typename T>
SimpleVector<T>::SimpleVector(size_t size)
:
data_{new T[size]},
end_{data_ + size},
capacity_{size}
{

}

template<typename T>
SimpleVector<T>::~SimpleVector() { delete[] data_; }

template<typename T>
T &SimpleVector<T>::operator[](size_t index) { return *(data_ + index); }

template<typename T>
T *SimpleVector<T>::end() { return end_; }

template<typename T>
T *SimpleVector<T>::begin() { return data_; }

template<typename T>
size_t SimpleVector<T>::Size() const { return end_ - data_; }

template<typename T>
size_t SimpleVector<T>::Capacity() const { return capacity_; }

template<typename T>
void SimpleVector<T>::PushBack(const T &value) {
    if (Size() >= Capacity()){
        Resize(Size() + 1);
    }
    *(end_++) = value;
}

template<typename T>
void SimpleVector<T>::Resize(size_t desired_size) {
    if (desired_size <= Capacity()){
        end_ = begin() + desired_size;
    } else {
        capacity_ = capacity_ == 0 ? 1 : max(capacity_ + capacity_, desired_size);
        T* new_data = new T[capacity_];
        size_t old_size = end() - begin();
//        if (data_ != nullptr){  // todo looks like it works, but better to find place in standard which describes it
            move(begin(), end(), new_data);  // not sure if it is safe to move zero length interval from nullptr
            delete[] data_;
//        }
        data_ = new_data;
        end_ = new_data + old_size;
    }
}

template<typename T>
void SimpleVector<T>::PushBack(T &&value) {
//    PushBack(move(value));
    if (Size() >= Capacity()){
        Resize(Size() + 1);
    }
    *(end_++) = move(value);
}

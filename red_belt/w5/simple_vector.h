#pragma once

#include <cstdlib>
#include <algorithm>

using namespace std;

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector()
            : data_{nullptr}, end_{nullptr}, capacity_{0}{
    }

    explicit SimpleVector(size_t size)
            :
            data_ {new T[size]},
            end_ {data_ + size},
            capacity_{size}
    {

    }


    SimpleVector(const SimpleVector& rhs)
            :
            data_ {new T[rhs.Size()]},
            end_ {data_ + rhs.Size()},
            capacity_{rhs.capacity_}
    {
        copy(rhs.begin(), rhs.end(), begin());
    }

    SimpleVector&operator=(const SimpleVector& rhs)
    {
        SimpleVector tmp(rhs);
        swap(end_, tmp.end_);
        swap(capacity_, tmp.capacity_);
        swap(data_, tmp.data_);
        return *this;
    }

    ~SimpleVector(){
        delete[] data_;
    }

    T& operator[](size_t index){
        return  data_[index] ;
    }

    T* begin() { return data_; };
    T* end() { return end_; };

    const T* begin() const{ return data_; };
    const T* end() const { return end_; };

    size_t Size() const{ return end_ - data_; }

    size_t Capacity() const { return capacity_; }

    bool Empty() const { return begin() == end(); }

    void PushBack(const T& value){
        if (Empty()){
            GrowVector(1);
        } else {
            if (Size() >= Capacity()){
                GrowVector(capacity_);
            }
        }
        (*end_) = value;
        ++end_;
    }

private:

    void GrowVector(size_t size){
        T* new_data = new T[capacity_ + size];
        copy(data_, end_, new_data);
        delete [] data_;
        data_ = new_data;
        end_ = new_data + capacity_;
        capacity_ += size;
    }

    T* data_;
    T* end_;
    size_t capacity_;
};

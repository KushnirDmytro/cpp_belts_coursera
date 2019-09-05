//
// Created by dkushn on 05.09.19.
//

#include <vector>
//#include <exception>
#include <stdexcept>
//#include "test_runner.h"

using namespace std;

template <typename T>
class Deque{

public:
    Deque() : front_vec{}, rear_vec{}{

    }

    explicit Deque(const vector<T> &init_vector) : front_vec{}, rear_vec{init_vector}{
    }

    bool Empty() const{
        return front_vec.empty() && rear_vec.empty();
    }

    size_t Size() const{
        return front_vec.size() + rear_vec.size();
    }

    T& operator[](size_t index){
        int aligned_index = index - front_vec.size();
        if (aligned_index < 0){
            return front_vec[front_vec.size() - index - 1];
        } else {
            return rear_vec[index - front_vec.size()];
        }
    }

    const T& operator[](size_t index) const{
//        cout << "Const access called" << endl;
        int aligned_index = index - front_vec.size();
        if (aligned_index < 0){
            return front_vec.at(front_vec.size() - index - 1);
        } else {
            return rear_vec.at(index - front_vec.size());
        }
    }

    T& At(size_t index) const{
        if (index >= Size()){
            throw out_of_range("");
        } else {
            return operator[](index);
        }
    }

    T& At(size_t index){
        if (index >= Size()){
            throw out_of_range("");
        } else {
            return operator[](index);
        }
    }

    T& Front() {
        return operator[](0);
    }
    const T& Front() const{
        return operator[](0);
    }
    T& Back(){
        return operator[](Size() - 1);
    }
    const T& Back() const{
        return operator[](Size() - 1);
    }

    void PushFront(const T &new_el){
        front_vec.push_back(new_el);
    }
    void PushBack(const T &new_el){
        rear_vec.push_back(new_el);
    }


//    константные и неконстантные версии методов Front и Back

private:
    vector<T> front_vec;
    vector<T> rear_vec;
};


void TestEmpty(){
    Deque<int> d;
    ASSERT(d.Empty());
    d.PushBack(1);
    ASSERT(!d.Empty());
    Deque<int> d2;
    ASSERT(d2.Empty());
    d2.PushFront(2);
    ASSERT(!d2.Empty());
}

void TestSize(){
    {
        Deque<int> d;
        ASSERT_EQUAL(d.Size(), 0);
        d.PushBack(1);
        ASSERT_EQUAL(d.At(0), 1);
        ASSERT_EQUAL(d.Size(), 1);
        d.PushBack(1);
        d.PushBack(1);
        ASSERT_EQUAL(d.Size(), 3);
    }
    {
        Deque<int> d;
        ASSERT_EQUAL(d.Size(), 0);
        d.PushFront(1);
        ASSERT_EQUAL(d.Size(), 1);
        ASSERT_EQUAL(d.At(0), 1);
        d.PushBack(1);
        d.PushBack(1);
        ASSERT_EQUAL(d.Size(), 3);
    }

}

void TestSqBraces(){
    {
        const Deque<int> d {{1}};
        ASSERT_EQUAL(d[0], 1);
        ASSERT_EQUAL(d.At(0), 1);

    }
    {
        Deque<int> d;
        d.PushBack(1);

        ASSERT_EQUAL(d[0], 1);
        d[0] = 2;
        ASSERT_EQUAL(d[0], 2);
        d.PushBack(3);
        ASSERT_EQUAL(d[1], 3);
    }
    {
        Deque<int> d;
        d.PushBack(1);

        ASSERT_EQUAL(d[0], 1);
        const int k = d[0];
    }
}


void TestFronBack(){
    {
        Deque<int> d;
        d.PushBack(1);
        ASSERT_EQUAL(d.Front(), 1);
        d.Front() = 2;
        ASSERT_EQUAL(d.Front(), 2);
        ASSERT_EQUAL(d.Back(), 2);
    }
    {
        const Deque<int> d {{1}};
//        d.PushBack(1);
        ASSERT_EQUAL(d.Front(), 1);
//        d.Front() = 2;
//        ASSERT_EQUAL(d.Front(), 2);
//        ASSERT_EQUAL(d.Back(), 2);
    }
}

int main(){
    TestRunner tr;
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestSize);
    RUN_TEST(tr, TestSqBraces);
    RUN_TEST(tr, TestFronBack);
}
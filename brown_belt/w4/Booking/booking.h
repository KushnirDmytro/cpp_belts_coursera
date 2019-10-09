//
// Created by dkushn on 07.10.19.
//

#ifndef CPP_BELTS_BOOKING_H
#define CPP_BELTS_BOOKING_H


#include <memory>
#include <utility>


namespace RAII{
    template <typename Provider>
    class Booking{
    private:
        Provider* provider_;
        int* counter_;
    public:
        Booking(Provider* p, int& counter)
        : provider_{p},
        counter_{&counter}
        {}

        Booking(const Booking&) = delete;
        void operator = (const Booking&) = delete;

        Booking (Booking &&b)
        : provider_{b.provider_},
        counter_{b.counter_}
        {
                b.provider_ = nullptr;
        }

        Booking& operator= (Booking&& b) {
            if (b != *this){
                std::swap(provider_, b.provider_);
                std::swap(counter_, b.counter_);
                // no need to explisitly call delete as with RAII we expect that other will call it upon destructor
            }
            return *this;
        }

        bool equals(const Booking& b) const { return provider_ == b.provider_ && counter_ == b.counter_;  }

        ~Booking(){
            if (provider_)
                provider_->CancelOrComplete(*this);
        }
    };

    template <typename Provider>
    bool operator==(const Booking<Provider>& lhs, const Booking<Provider>& rhs){ return lhs.equals(rhs); }

    template <typename Provider>
    bool operator!=(const Booking<Provider>& lhs, const Booking<Provider>& rhs){ return ! (lhs == rhs);  }
}

#endif //CPP_BELTS_BOOKING_H

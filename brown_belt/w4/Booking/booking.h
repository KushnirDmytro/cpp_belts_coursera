//
// Created by dkushn on 07.10.19.
//

#ifndef CPP_BELTS_BOOKING_H
#define CPP_BELTS_BOOKING_H

namespace RAII{
    template <typename Provider>
    class Booking{
    private:
        Provider provider_;
    public:
        Booking(Provider p) : provider_{p} {}
    };
}

#endif //CPP_BELTS_BOOKING_H

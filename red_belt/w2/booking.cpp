//
// Created by dkushn on 07.09.19.
//

#include <vector>
#include <set>
#include <map>
#include <deque>
#include <iostream>
#include <utility>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "test_runner.h"

using namespace std;

using bookin_time_t = int64_t ;
using client_id_t = uint32_t ;
using n_rooms_t = uint64_t ;

using  record = pair<client_id_t, n_rooms_t>;
using  hotel_daylog = deque< pair <bookin_time_t, record> >;

struct HotelInfo{
//    hotel_daylog log;
    n_rooms_t rooms;
    n_rooms_t clients;
    map<client_id_t, int> active_bookings;
};


struct Event{
    int64_t time;
    string hotel_name;
    client_id_t id;
    n_rooms_t rooms;
};

class BookingManager{
public:
    BookingManager()  = default;

    void Book(
            const bookin_time_t &t,
            const string &hotel_name,
            const client_id_t &cl_id,
            const n_rooms_t &n_r){
        auto &referenced_hotel = booked[hotel_name];

        if (n_r != 0){ // TODO check if it is required
            int old_booking = referenced_hotel.active_bookings[cl_id]++;
            if (old_booking == 0){
                referenced_hotel.clients += 1;
            }
            global_journal.push_back({t, hotel_name, cl_id, n_r});
            referenced_hotel.rooms += n_r;
        }

        expired_timestamp = t - DAY_SPAN;
        UpdateDaylog();
    }

    void Book(const Event &ev){
        Book(ev.time, ev.hotel_name, ev.id, ev.rooms);
    }


    int Rooms(const string &h_name){
        return booked[h_name].rooms;
    }

    int Clients(const string &h_name) {
        return  booked[h_name].clients;
    }

private:
    void UpdateDaylog(){
        while ( !global_journal.empty() && global_journal.front().time <= expired_timestamp){
            auto &info_token = global_journal.front();
            HotelInfo& updated_hotel = booked[info_token.hotel_name];
            updated_hotel.rooms -= info_token.rooms;
            updated_hotel.active_bookings[info_token.id] -= 1;
            if (updated_hotel.active_bookings[info_token.id] == 0){
                updated_hotel.active_bookings.erase(info_token.id);
                updated_hotel.clients -= 1;
            }
            global_journal.pop_front();
        }

    }

    map<string, HotelInfo> booked;
    bookin_time_t expired_timestamp;
    deque<Event> global_journal;
    static const int DAY_SPAN = 86'400;
};


// ========================   TESTS

//void TestAddRequest() {
//    {
//        BookingManager M;
//        vector<Event> request_empty = {};
//        vector<Event> request1 = {{10, "A", 10000, 100}};
//        vector<Event> request2 = {{10, "A", 10000, 100}, {10, "A", 20000, 100}};
//        vector<Event> request3 = {{10, "A", 10000, 100}, {10, "A", 20000, 100},
//                                    {10, "B", 10000, 100}};
//        M.Book(10, "A", 10000, 100);
//        ASSERT_EQUAL(M.GetRequests(0), request_empty);
//        ASSERT_EQUAL(M.GetRequests(10), request1);
//        M.Book(10, "A", 20000, 100);
//        ASSERT_EQUAL(M.GetRequests(10), request2);
//        M.Book(10, "B", 10000, 100);
//        ASSERT_EQUAL(M.GetRequests(10), request3);
//
//    }
//    {
//        BookingManager M;
//        vector<Event> request_empty = {};
//        int64_t t1 = 1000;
//        int64_t t2 = 2000;
//        int64_t t3 = 10000;
//        int64_t t4 = 86'399;  //'
//        int64_t t5 = 86'400;  //'
//        int64_t t6 = 87'400;  //'
//        int64_t t7 = 1'000'000;
//        int64_t t8 = 1'000'000'000'000;
//        vector<Event> request1 = {{t1, "A", 10000, 100}};
//        vector<Event> request2 = {{t2, "A", 20000, 100}};
//        vector<Event> request3 = {{t3, "B", 10000, 100}};
//        vector<Event> request4 = {{t4, "B", 20000, 100}};
//        vector<Event> request5 = {{t5, "C", 10000, 100}};
//        vector<Event> request6 = {{t6, "C", 20000, 100}};
//        vector<Event> request7 = {{t7, "D", 100000, 100}};
//        vector<Event> request8 = {{t8, "D", 200000, 100}};
//
//        M.Book(t1, "A", 10000, 100);
//        ASSERT_EQUAL(M.GetRequests(0), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t1), request1);
//
//        M.Book(t2, "A", 20000, 100);
//        ASSERT_EQUAL(M.GetRequests(0), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t1), request1);
//        ASSERT_EQUAL(M.GetRequests(t2), request2);
//
//        M.Book(t3, "B", 10000, 100);
//        ASSERT_EQUAL(M.GetRequests(0), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t1), request1);
//        ASSERT_EQUAL(M.GetRequests(t2), request2);
//        ASSERT_EQUAL(M.GetRequests(t3), request3);
//
//        M.Book(t4, "B", 20000, 100);
//        ASSERT_EQUAL(M.GetRequests(0), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t1), request1);
//        ASSERT_EQUAL(M.GetRequests(t2), request2);
//        ASSERT_EQUAL(M.GetRequests(t3), request3);
//        ASSERT_EQUAL(M.GetRequests(t4), request4);
//
//        M.Book(t5, "C", 10000, 100);
//        ASSERT_EQUAL(M.GetRequests(0), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t4), request4);
//        ASSERT_EQUAL(M.GetRequests(t5), request5);
//
//        M.Book(t6, "C", 20000, 100);
//        ASSERT_EQUAL(M.GetRequests(t1), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t3), request3);
//        ASSERT_EQUAL(M.GetRequests(t6), request6);
//
//        M.Book(t7, "D", 100000, 100);
//        ASSERT_EQUAL(M.GetRequests(t3), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t5), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t7), request7);
//
//        M.Book(t8, "D", 200000, 100);
//        ASSERT_EQUAL(M.GetRequests(t4), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t6), request_empty);
//        ASSERT_EQUAL(M.GetRequests(t8), request8);
//
//    }
//}

void TestGetRooms() {
    {
        BookingManager M;
        int i = 0;
        vector<int> rooms = {10, 20, 30, 40, 50, 50, 10};
        vector<int> times = {10, 2000, 30000, 80000, 86399, 86410, 1000000};
        M.Book(times[i], "A", 10000, 10);
        M.Book(times[i], "B", 10000, 10);
        ASSERT_EQUAL(M.Rooms("A"), rooms[i++]);
        M.Book(times[i], "A", 20000, 5);
        M.Book(times[i], "A", 20000, 5);
        M.Book(times[i], "B", 20000, 10);
        ASSERT_EQUAL(M.Rooms("A"), rooms[i++]);
        M.Book(times[i], "A", 10000, 10);
        M.Book(times[i], "B", 10000, 10);
        ASSERT_EQUAL(M.Rooms("A"), rooms[i++]);
        M.Book(times[i], "A", 30000, 10);
        M.Book(times[i], "C", 30000, 10);
        ASSERT_EQUAL(M.Rooms("A"), rooms[i++]);
        M.Book(times[i], "A", 40000, 10);
        M.Book(times[i], "C", 40000, 10);
        ASSERT_EQUAL(M.Rooms("A"), rooms[i++]);
        M.Book(times[i], "A", 30000, 10);
        M.Book(times[i], "C", 30000, 10);
        ASSERT_EQUAL(M.Rooms("A"), rooms[i++]);
        M.Book(times[i], "A", 50000, 10);
        M.Book(times[i], "C", 50000, 10);
        ASSERT_EQUAL(M.Rooms("A"), rooms[i++]);

    }
}
void TestGetClients() {
    {
        BookingManager M;
        int i = 0;
        vector<int> clients = {1, 2, 2, 3, 3, 4, 1};
        vector<int> times = {10, 2000, 30000, 80000, 86399, 86410, 1'000'000};
        M.Book(times[i], "A", 1000, 0);               //  == "A": -, t = 10
        M.Book(times[i], "A", 10000, 10);             //  + 1 "A": "1", t = 10
        M.Book(times[i], "B", 10000, 10);             //  + 1 "B": "1", t = 10
        ASSERT_EQUAL(M.Clients("A"), clients[i]);
        ASSERT_EQUAL(M.Clients("B"), clients[i++]);
        M.Book(times[i], "A", 20000, 10);             //  +1 "A": "1" + "2", t = 2000
        M.Book(times[i], "A", 20000, 10);             //  == "A": "1" + "2", t = 2000
        M.Book(times[i], "B", 20000, 10);             //  +1 "B": "1" + "2", t = 2000
//        cout << M.Clients("A") << "--" << clients[i] << endl;
        ASSERT_EQUAL(M.Clients("A"), clients[i]);
        ASSERT_EQUAL(M.Clients("B"), clients[i++]);
        M.Book(times[i], "A", 10000, 10);             //  == "A": "1" + "2", t = 30000
        M.Book(times[i], "A", 20000, 10);             //  == "A": "1" + "2", t = 30000
        M.Book(times[i], "B", 10000, 10);             //  == "B": "1" + "2", t = 30000
        ASSERT_EQUAL(M.Clients("A"), clients[i]);
        ASSERT_EQUAL(M.Clients("B"), clients[i++]);
        M.Book(times[i], "A", 30000, 10);             //  +1 "A": "1" + "2" + "3", t = 80000
        M.Book(times[i], "B", 30000, 10);             //  +1 "B": "1" + "2" + "3", t = 80000
        M.Book(times[i], "C", 10000, 10);             //  +1 "C": "1", t = 80000
        M.Book(times[i], "C", 20000, 10);             //  +1 "C": "1" + "2", t = 80000
        M.Book(times[i], "C", 30000, 10);             //  +1 "C": "1" + "2" + "3", t = 80000
        ASSERT_EQUAL(M.Clients("A"), clients[i]);
        ASSERT_EQUAL(M.Clients("B"), clients[i]);
        ASSERT_EQUAL(M.Clients("C"), clients[i++]);
        M.Book(times[i], "A", 10000, 10);             // == "A", t = 86399
        M.Book(times[i], "B", 10000, 10);             // == "B", t = 86399
        M.Book(times[i], "C", 10000, 10);             // == "C", t = 86399
        ASSERT_EQUAL(M.Clients("A"), clients[i]);
        ASSERT_EQUAL(M.Clients("B"), clients[i]);
        ASSERT_EQUAL(M.Clients("C"), clients[i++]);
        M.Book(times[i], "A", 40000, 10);         // -t = 10, +1 "A": "1"+"2"+"2"+"4", t = 86410
        M.Book(times[i], "B", 40000, 10);         // -t = 10, +1 "B": "1"+"2"+"2"+"4", t = 86410
        M.Book(times[i], "C", 40000, 10);         // -t = 10, +1 "B": "1"+"2"+"2"+"4", t = 86410
        ASSERT_EQUAL(M.Clients("A"), clients[i]);
        ASSERT_EQUAL(M.Clients("B"), clients[i]);
        ASSERT_EQUAL(M.Clients("C"), clients[i++]);
        M.Book(times[i], "A", 50000, 10);         // -t = 8641, -3 "A": "5", t = 1'000'000
        M.Book(times[i], "B", 50000, 10);         // -t = 8641, -3 "B": "5", t = 1'000'000
        M.Book(times[i], "C", 50000, 10);         // -t = 8641, -3 "B": "5", t = 1'000'000
        ASSERT_EQUAL(M.Clients("A"), clients[i]);
        ASSERT_EQUAL(M.Clients("B"), clients[i]);
        ASSERT_EQUAL(M.Clients("C"), clients[i++]);
    }
}
void TestClients() {
    {
    BookingManager bm;
    Event e1{0, "q", 0, 1};
    bm.Book(e1);
    ASSERT_EQUAL(bm.Clients("q"), 1);
    ASSERT_EQUAL(bm.Rooms("q"), 1);
    Event e2{10, "q", 0, 3};
    bm.Book(e2);
    ASSERT_EQUAL(bm.Clients("q"), 1);
    ASSERT_EQUAL(bm.Rooms("q"), 4);
    Event e3{86411, "q", 3, 1};
    bm.Book(e3);
//    cout << bm.Clients("q") << endl;
    ASSERT_EQUAL(bm.Clients("q"), 1);
    ASSERT_EQUAL(bm.Rooms("q"), 1);
}
    {
        BookingManager bm;
        ASSERT_EQUAL(bm.Clients("Marriott"), 0);
        ASSERT_EQUAL(bm.Rooms("Marriott"), 0);
        Event e1{ 10, "FourSeasons", 1, 2 };
        Event e2{ 10, "Marriott", 1, 1 };
        Event e3{ 86409, "FourSeasons", 2, 1 };
        bm.Book(e1);
        bm.Book(e2);
        bm.Book(e3);
        ASSERT_EQUAL(bm.Clients("FourSeasons"), 2);
        ASSERT_EQUAL(bm.Rooms("FourSeasons"), 3);
        ASSERT_EQUAL(bm.Rooms("Marriott"), 1);
        Event e4{ 86410, "Marriott", 2, 10 };
        bm.Book(e4);
        ASSERT_EQUAL(bm.Rooms("FourSeasons"), 1);
        ASSERT_EQUAL(bm.Rooms("Marriott"), 10);
    }

}


int main() {
    try {


//        TestRunner tr;
//        RUN_TEST(tr, TestClients);
//        RUN_TEST(tr, TestGetRooms);
//        RUN_TEST(tr, TestGetClients);

    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false); // FIXME
    cin.tie(nullptr);

    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        try{

            string query_type;
            cin >> query_type;

            string hotel_name;
            if (query_type == "BOOK") {
                int64_t time;
                int client_id;
                int room_count;
                cin >> time >> hotel_name >> client_id >> room_count;
                manager.Book(time, hotel_name, client_id, room_count);
            } else {
                cin >> hotel_name;
                if (query_type == "ROOMS")
                    cout << manager.Rooms(hotel_name) << endl;
                if (query_type == "CLIENTS")
                    cout << manager.Clients(hotel_name) << endl;
            }
        } catch (exception &e){
            cout << e.what() << endl;
        }
    }

    return 0;
    } catch (exception &ex){
        cout << "Outer exception [" << ex.what() << "]" << endl;
    }

}


/*
 11
CLIENTS Marriott
ROOMS Marriott
BOOK 10 FourSeasons 1 2
BOOK 10 Marriott 1 1
BOOK 86409 FourSeasons 2 1
CLIENTS FourSeasons
ROOMS FourSeasons
CLIENTS Marriott
BOOK 86410 Marriott 2 10
ROOMS FourSeasons
ROOMS Marriott

0
0
2
3
1
1
10

 * */
//
// Created by dkushn on 22.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
using namespace std;

// Дана структура LectureTitle:
//

string A(){
    return "A";
}
string B(const string& ar){
    cout << ar << endl;
}

struct Specialization{
    string value;
    explicit Specialization(const string &new_val){
        value = new_val;
    }
};

struct Course{
    string value;
    explicit Course(const string &new_val){
        value = new_val;
    }
};
struct Week{
    string value;
    explicit Week(const string &new_val){
        value = new_val;
    }
};
struct LectureTitle {
    LectureTitle(const Specialization &spec, const Course& course, const Week &week) :
            specialization{spec.value},
            course{course.value},
            week{week.value}{
    }

    string specialization;
    string course;
    string week;
};
//};Допишите конструктор и структуры Specialization, Course, Week так, чтобы объект LectureTitle можно было создать с помощью кода
LectureTitle title(
        Specialization("C++"),
        Course("White belt"),
        Week("4th")
);

int main(){
//    const vector<int> a {1, 2, 4};
//    a[0] = 3;
}

//но нельзя было с помощью следующих фрагментов кода:

//LectureTitle title("C++", "White belt", "4th");
//
//LectureTitle title(string("C++"), string("White belt"), string("4th"));
//
//LectureTitle title = {"C++", "White belt", "4th"};
//
//LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};
//
//LectureTitle title(
//        Course("White belt"),
//        Specialization("C++"),
//        Week("4th")
//);
//
//LectureTitle title(
//        Specialization("C++"),
//        Week("4th"),
//        Course("White belt")
//);

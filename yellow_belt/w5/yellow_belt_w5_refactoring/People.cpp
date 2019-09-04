
#include <string>
#include <iostream>

#include "People.h"

using namespace std;


Person::Person(const string &new_persons_name, const string &profession) : Name_{new_persons_name}, Profession_{profession}
{
}

void Person::Walk(const string& destination) const{
    cout << Profession_ << ": " << Name_ << " walks to: " << destination << endl;
}



Student::Student(const string &name, const string &favouriteSong)  // I know about using std::move but this referes to next belt
        : Person{name, "Student"}, FavouriteSong_{favouriteSong}
{
}

void Student::SingSong() const{
    cout << "Student: " << Name_ << " sings a song: " << FavouriteSong_ << endl;
}

void Student::Walk(const string &destination) const{
    Person::Walk(destination);
    SingSong();
}

void Student::Learn() {
    cout << "Student: " << Name_ << " learns" << endl;
}



Teacher::Teacher(const string &name, const string &subject)
        : Person(name, "Teacher"), Subject{subject}
{
}

void Teacher::Teach() const{
    cout << "Teacher: " << Name_ << " teaches: " << Subject << endl;
}

Policeman::Policeman(const string &name)
        : Person(name, "Policeman")
{
}


void Policeman::Check(const Person &p) const{
    cout << "Policeman: " << Name_ << " checks " << p.Profession_ << ". " << p.Profession_ << "'s name is: " << p.Name_ << endl;
}

void VisitPlaces(const Person &person, const vector<string> &places) {
    for (const auto &p : places) {
        person.Walk(p);
    }
}
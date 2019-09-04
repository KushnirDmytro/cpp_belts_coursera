#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:

    explicit Person(const string& name, const string& activity) :
            name_(name), activity_(activity) {};

    virtual void Walk(const string& destination) const {
        cout << activity_ << ": " << name_ << " walks to: " << destination << endl;
    }

    string GetName() const {
        return name_;
    }

    string GetActivity() const {
        return activity_;
    }


protected:
    const string name_, activity_;
};


class Student : public Person {
public:

    explicit Student(const string& name, const string& favourite_song) :
            Person(name, "Student"), favourite_song_(favourite_song) {};

    void Learn() const {
        cout << "Student: " << name_ << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << "Student: " << name_ << " sings a song: " << favourite_song_ << endl;
    }


private:
    const string favourite_song_;
};


class Teacher : public Person {
public:

    explicit Teacher(const string& name, const string& subject) :
            Person(name, "Teacher"), subject_(subject) {};

    void Teach() const {
        cout << "Teacher: " << name_ << " teaches: " << subject_ << endl;
    }


private:
    const string subject_;
};


class Policeman : public Person {
public:

    explicit Policeman(const string& name) : Person(name, "Policeman") {};

    void Check(const Person& person) const {
        cout << "Policeman: " << name_ << " checks " << person.GetActivity() << ". "
             << person.GetActivity() << "'s name is: " << person.GetName() << endl;
    }
};


void VisitPlaces(const Person& person, const vector<string>& places) {
    for (const string& place : places) {
        person.Walk(place);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
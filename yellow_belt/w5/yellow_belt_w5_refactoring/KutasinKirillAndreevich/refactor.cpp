#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person{
public:
    Person(const string& name,
           const string& job )
            : Name(name), Job(job) {}

    string Head() const{
        return Job+": "+Name;
    }

    virtual void Walk(const string &destination) const {
        cout<< Head() << " walks to: " << destination << endl;
    }

    const string Name;
    const string Job;
};

class Student : public Person {
public:
    Student(const string& name,
            const string& favouriteSong)
            : Person(name,"Student"),
              FavouriteSong(favouriteSong){}

    void Learn() const {
        cout << Head() << " learns" << endl;
    }

    void Walk(const string& destination) const  override {
        cout << Head() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const  {
        cout << Head() << " sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;
};


class Teacher: public Person {
public:
    Teacher(const string& name,
            const string& subject)
            : Person(name,"Teacher"),
              Subject(subject){}

    void Teach() const {
        cout << Head() << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name)
            : Person(name,"Policeman"){}

    void Check(const Person& h) const {
        cout << Head() << " checks " << h.Job << ". " << h.Job << "'s name is: " << h.Name << endl;
    }
};

void VisitPlaces(const Person& h,const vector<string>& places) {
    for (auto p : places) {
        h.Walk(p);
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
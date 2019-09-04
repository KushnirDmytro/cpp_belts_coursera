#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Human {
public:
    Human(const string& name, const string& profession) : Name(name), Profession(profession) {}
    virtual void Walk(const string& destination) const {
        cout << Profession << ": " << Name << " walks to: " << destination << endl;
    }
    string GetName() const {return Name;}
    string GetProfession() const {return Profession;}
    const string Name;
    const string Profession;

};

class Student : public Human {
public:
    Student(const string& name, const string& favouriteSong) : Human(name, "Student"), FavouriteSong(favouriteSong) {}
    void Learn() {cout << "Student: " << Name << " learns" << endl;}
    void Walk(const string& destination) const override {
        cout << Profession << ": " << Name << " walks to: " << destination << endl;
        SingSong();
    }


    void SingSong() const {cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;}
private:
    const string FavouriteSong;

};
class Teacher : public Human {
public:
    Teacher(const string& name,const string& subject) : Human(name,"Teacher"),Subject(subject) {}
    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }
private:
    const string Subject;
};

class Policeman : public Human {
public:
    Policeman(const string& name) : Human(name,"Policeman") {}
    void Check(const Human& h) {
        cout << "Policeman: " << Name << " checks " << h.GetProfession() << ". " << h.GetProfession() << "'s name is: " << h.GetName() << endl;
    }
};

void VisitPlaces(const Human&  h,const vector<string>& places) {
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
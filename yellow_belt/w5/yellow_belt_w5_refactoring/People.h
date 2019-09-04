
#ifndef CPP_BELTS_PEOPLE_H
#define CPP_BELTS_PEOPLE_H

#include <string>
#include <vector>

using namespace std;

class Policeman;

class Person{
public:
    Person(const string& new_persons_name, const string& profession);
    virtual void Walk(const string& destination) const;

protected:
    const string Name_;
    const string Profession_;

    friend Policeman;
};


class Student : public Person{
public:
    Student(const string &name, const string &favouriteSong);
    void Learn();  // let's imagine that this action changes student's state. At least mental.
    void Walk(const string &destination) const override;
    void SingSong() const;

private:
    const string FavouriteSong_;
};


class Teacher : public Person {
public:
    Teacher(const string &name, const string &subject);
    void Teach() const;

private:
    const string Subject;
};



class Policeman : public Person{
public:
    explicit Policeman(const string &name);
    void Check(const Person &p) const;
};


void VisitPlaces(const Person &person, const vector<string> &places);



#endif //CPP_BELTS_PEOPLE_H

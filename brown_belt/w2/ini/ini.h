//
// Created by dkushn on 23.09.19.
//
#pragma once
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

ostream& operator<<(ostream& os, const unordered_map<string, string> &sec);

namespace Ini{


using Section = unordered_map<string, string>;

class Document {
public:
    Section& AddSection(string name);
    const Section& GetSection(const string& name) const;
    size_t SectionCount() const;

private:
    unordered_map<string, Section> sections;
};


Document Load(istream& input);

}
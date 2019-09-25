//
// Created by dkushn on 23.09.19.
//
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>

#include "ini.h"

using namespace std;


ostream& operator<<(ostream& os, const unordered_map<string, string> &sec){
    for (const auto &el_sec : sec){
        os << el_sec.first << ":" << el_sec.second << '\n';
    }
    return os;
}

namespace Ini{

//using Section = unordered_map<string, string>;


    Document Load(istream &input) {
        string line;
        Document new_document;
        Section *section_addr{nullptr};
        string key_buf, val_buf;
        while (getline(input, line)){
            char first_char = line[0];
            switch (first_char){
                case '\0':
                    break;
                case '[':{
                    string section_name = line.substr(1, line.size() - 2); // stripping braces
                    section_addr = &(new_document.AddSection(section_name));
                    break;
                }
                default:{
                    size_t split_position = line.find('=');
                    key_buf = line.substr(0, split_position);
                    val_buf = line.substr(split_position + 1); // up to the end
                    section_addr->insert({key_buf, val_buf});
                }
            }
        }
        return new_document;
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    const Section &Document::GetSection(const string &name) const {
        return sections.at(name);
    }

    Section &Document::AddSection(string name) {
        auto [it, is_inserted] =
                sections.insert({move(name), {}});
        return it->second;
    }
}

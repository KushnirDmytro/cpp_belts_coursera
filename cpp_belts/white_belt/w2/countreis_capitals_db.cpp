//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
using namespace std;

/*
 in:
6
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
ABOUT RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
DUMP


 out:
Introduce new country RussianEmpire with capital Petrograd
Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
Country RussianRepublic has capital Petrograd
Country RussianRepublic with capital Petrograd has been renamed to USSR
Country USSR has changed its capital from Petrograd to Moscow
USSR/Moscow

in:
 24
RENAME FakeCountry FarFarAway
ABOUT FarFarAway
DUMP
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL ColonialBrazil Salvador
CHANGE_CAPITAL TsardomOfRussia SaintPetersburg
RENAME TsardomOfRussia RussianEmpire
CHANGE_CAPITAL RussianEmpire Moscow
CHANGE_CAPITAL RussianEmpire SaintPetersburg
CHANGE_CAPITAL ColonialBrazil RioDeJaneiro
DUMP
RENAME ColonialBrazil EmpireOfBrazil
ABOUT RussianEmpire
RENAME EmpireOfBrazil UnitedStatesOfBrazil
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia
RENAME UnitedStatesOfBrazil FederativeRepublicOfBrazil
ABOUT RussianEmpire
DUMP
RENAME USSR USSR


out:
 Incorrect rename, skip
Country FarFarAway doesn't exist
There are no countries in the world
Introduce new country TsardomOfRussia with capital Moscow
Country TsardomOfRussia hasn't changed its capital
Introduce new country ColonialBrazil with capital Salvador
Country TsardomOfRussia has changed its capital from Moscow to SaintPetersburg
Country TsardomOfRussia with capital SaintPetersburg has been renamed to RussianEmpire
Country RussianEmpire has changed its capital from SaintPetersburg to Moscow
Country RussianEmpire has changed its capital from Moscow to SaintPetersburg
Country ColonialBrazil has changed its capital from Salvador to RioDeJaneiro
ColonialBrazil/RioDeJaneiro RussianEmpire/SaintPetersburg
Country ColonialBrazil with capital RioDeJaneiro has been renamed to EmpireOfBrazil
Country RussianEmpire has capital SaintPetersburg
Country EmpireOfBrazil with capital RioDeJaneiro has been renamed to UnitedStatesOfBrazil
Country RussianEmpire has changed its capital from SaintPetersburg to Petrograd
Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
Country RussianRepublic with capital Petrograd has been renamed to USSR
Country USSR has changed its capital from Petrograd to Moscow
Country UnitedStatesOfBrazil has changed its capital from RioDeJaneiro to Brasilia
Country UnitedStatesOfBrazil with capital Brasilia has been renamed to FederativeRepublicOfBrazil
Country RussianEmpire doesn't exist
FederativeRepublicOfBrazil/Brasilia USSR/Moscow
Incorrect rename, skip

 */




//Реализуйте справочник столиц стран.
//
//На вход программе поступают следующие запросы:
//
//CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital, либо добавление такой страны с такой столицей, если раньше её не было.
//RENAME old_country_name new_country_name — переименование страны из old_country_name в new_country_name.
//ABOUT country — вывод столицы страны country.
//DUMP — вывод столиц всех стран.
//Формат ввода
//В первой строке содержится количество запросов Q, в следующих Q строках — описания запросов. Все названия стран и столиц состоят лишь из латинских букв, цифр и символов подчёркивания.
//
//Формат вывода
//Выведите результат обработки каждого запроса:
//
//В ответ на запрос CHANGE_CAPITAL country new_capital выведите
//Introduce new country country with capital new_capital, если страны country раньше не существовало;
//Country country hasn't changed its capital, если страна country до текущего момента имела столицу new_capital;
//Country country has changed its capital from old_capital to new_capital, если страна country до текущего момента имела столицу old_capital, название которой не совпадает с названием new_capital.
//В ответ на запрос RENAME old_country_name new_country_name выведите
//Incorrect rename, skip, если новое название страны совпадает со старым, страна old_country_name не существует или страна new_country_name уже существует;
//Country old_country_name with capital capital has been renamed to new_country_name, если запрос корректен и страна имеет столицу capital.
//В ответ на запрос ABOUT country выведите
//Country country doesn't exist, если страны с названием country не существует;
//Country country has capital capital, если страна country существует и имеет столицу capital.
//В ответ на запрос DUMP выведите
//There are no countries in the world, если пока не было добавлено ни одной страны;
//разделённые пробелами пары country/capital, описывающие столицы всех стран и упорядоченные по названию страны, если в мире уже есть хотя бы одна страна.


template<class T> ostream& operator<<(ostream& os, vector<T> v){
    for (const auto &s: v){
        cout << s << " ";
    }
    return os;
}

template <class K, class V> ostream& operator <<(ostream& os, const map<K,V> &m){
    for (const auto& item: m){
        cout << item.first << "/" << item.second << " ";
    }
    return os;
}


enum commands{
    CHANGE_CAPITAL, RENAME, ABOUT, DUMP
};

map<string, commands> known_commands{
        {"CHANGE_CAPITAL", CHANGE_CAPITAL},
        {"RENAME",RENAME},
        {"ABOUT",ABOUT},
        {"DUMP",DUMP}
};

void change_country(map<string, string> &c2c, const string &country, const string &new_capital){
    if (c2c.count(country) == 0){
        cout << "Introduce new country " <<  country << " with capital " << new_capital << endl;
    }
    else{
        if (c2c[country] == new_capital){
            cout << "Country " << country << " hasn't changed its capital" <<endl;
        }
        else{
            cout << "Country " << country << " has changed its capital from " << c2c[country] << " to " << new_capital << endl;
        }
    }
    c2c[country] = new_capital;
}

void rename(map<string, string> &c2c, const string &old_country_name, const string &new_country_name){
    if (c2c.count(old_country_name) == 0 || new_country_name == old_country_name || c2c.count(new_country_name) != 0){
        cout << "Incorrect rename, skip" << endl;
    }
    else{
        cout << "Country " << old_country_name << " with capital " << c2c[old_country_name] << " has been renamed to " << new_country_name << endl;
        c2c[new_country_name] = c2c[old_country_name];
        c2c.erase(old_country_name);
    }
}

void about(const map<string, string> &c2c, string &country){
    if (c2c.count(country) == 0){
        cout << "Country " << country << " doesn't exist" << endl;
    }
    else{
        cout << "Country " << country << " has capital "<< c2c.at(country) << endl;
    }
}

void dump(const map<string, string> c2c){
    if (c2c.empty()){
        cout << "There are no countries in the world" << endl;
    }
    else{
        cout << c2c << endl;
    }
}

int main() {


    int N;
    cin >> N;
    string A, B;
    string command;

    map<string, string> c2c; // country-to-capital

    for (int i = 0; i < N; ++i){
        cin >> command;
        commands com = known_commands[command];

        switch (com){
            case CHANGE_CAPITAL:{
                string country, new_capital;
                cin >> country >> new_capital;
                change_country(c2c, country, new_capital);
            }
                break;
            case RENAME:{
                string old_country_name, new_country_name;
                cin >> old_country_name >> new_country_name;
                rename(c2c, old_country_name, new_country_name);
            }
                break;
            case ABOUT:{
                string country;
                cin >> country;
                about(c2c, country);
            }
                break;

            case DUMP:{
                dump(c2c);
            }
                break;
        }
    }

}

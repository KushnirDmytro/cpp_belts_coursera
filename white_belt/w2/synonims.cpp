//
// Created by dkushn on 21.07.19.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
using namespace std;

/*
 in:
8
ADD program code
COUNT cipher
ADD code cipher
COUNT code
COUNT program
CHECK code program
CHECK program cipher
CHECK cpp java


 out:
0
2
1
YES
NO
NO

 */



//Два слова называются синонимами друг друга, если они имеют похожие значения. Реализуйте следующие операции над словарём синонимов:
//
//ADD word1 word2 — добавить в словарь пару синонимов (word1, word2).
//COUNT word — узнать количество синонимов слова word.
//CHECK word1 word2 — проверить, являются ли слова word1 и word2 синонимами. Слова word1 и word2 считаются синонимами,
// если среди запросов ADD был хотя бы один запрос ADD word1 word2 или ADD word2 word1.
//Формат ввода
//Сначала вводится количество запросов Q, затем Q строк с описаниями запросов.
// Гарантируется, что в каждом запросе CHECK и ADD слова word1 и word2 различны. Все слова состоят лишь из латинских букв, цифр и символов подчёркивания.
//
//Формат вывода
//Для каждого запроса в соответствующей строке выведите ответ на него:
//
//В ответ на запрос COUNT word выведите единственное целое число — количество синонимов слова word.
//В ответ на запрос CHECK word1 word2 выведите строку YES, если word1 и word2 являются синонимами, и NO в противном случае.


enum Commands{
    ADD, CHECK, COUNT
};

map<string, Commands> known_commands{
        {"ADD", ADD},
        {"CHECK", CHECK},
        {"COUNT", COUNT}
};

int main() {
    int Q;
    cin >> Q;
    string command;
    map<string, set<string>> synonimical;

    for (int i = 0; i < Q; ++i){
        cin >> command;
        Commands com = known_commands[command];
        switch (com){
            case (ADD):{
                string w1, w2;
                cin >> w1 >> w2;
                synonimical[w1].insert(w2);
                synonimical[w2].insert(w1);
                break;
            }
            case (CHECK):{
                string w1, w2;
                cin >> w1 >> w2;
                if (synonimical.count(w1) != 0){
                    if (synonimical[w1].count(w2) != 0){
                        cout << "YES" << endl;
                    }
                    else{
                        cout << "NO" << endl;
                    }
                }
                else{
                    cout << "NO" << endl;
                }
                break;
            }
            case (COUNT):{
                string w;
                cin >> w;
                if (synonimical.count(w) != 0){
                    cout << synonimical[w].size() << endl;
                }
                else{
                    cout << 0 << endl;
                }
                break;
            }
        }
    }
}

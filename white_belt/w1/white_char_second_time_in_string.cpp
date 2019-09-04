#include <iostream>
#include <cmath>

using namespace std;

//Дана строка. Найдите в этой строке второе вхождение буквы f и выведите индекс этого вхождения.
// Если буква f в данной строке встречается только один раз, выведите число -1, а если не встречается ни разу, выведите число -2. Индексы нумеруются с нуля.


/*
stdin	stdout
comfort	-1
coffee	3
car	-2
 */


int main() {

    string s;

    cin >> s;
    char wanted = 'f';
    int detected_n_wanted {0};
    for (size_t i = 0; i < s.length(); ++i){
        if (s[i] == wanted){
            ++detected_n_wanted;
            if (detected_n_wanted == 2){
                cout << i << endl;
                return 0;
            }
        }
    }
    if (detected_n_wanted == 0){
        cout << -2 << endl;
    } else if (detected_n_wanted == 1) {
        cout << -1 << endl;
    } else {
        cout << "You not suppose to see this" << endl;
    }

    return 0;
}
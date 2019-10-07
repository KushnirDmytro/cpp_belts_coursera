#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <sstream>
#include <fstream>

using namespace std;


void foo(ostream& os){
    os << "blah" <<endl;
}

int main() {

    ofstream foo_f ("../f3");

    ostringstream os("");
    foo(foo_f);
//    cout << is.str() << endl;

    cout << os.str() << endl;

    return 0;
}
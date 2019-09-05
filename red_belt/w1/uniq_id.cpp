#include <string>
#include <vector>
using namespace std;

#define CALL_B(ARG) _BLAH_##ARG
#define CALL_A(line_n) CALL_B(line_n)
#define UNIQ_ID CALL_A(__LINE__)  // Реализуйте этот макрос так, чтобы функция main компилировалась

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
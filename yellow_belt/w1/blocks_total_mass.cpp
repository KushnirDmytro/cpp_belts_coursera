#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;



int main() {
    size_t n_blocks, ro_blocks;
    cin >> n_blocks >> ro_blocks;
    uint64_t a, b, c, total_mass{0};
    for (size_t i = 0; i < n_blocks; ++i){
        cin >> a >> b >> c;
        total_mass +=  a * b * c * ro_blocks;
    }
    cout << total_mass;
    return 0;
}


/*

 * */
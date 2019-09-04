#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

class Matrix{
    vector<vector<int>> mat_;

public:
    Matrix():mat_{}{
    }
    Matrix(int num_rows, int num_cols){
        Reset(num_rows, num_cols);
    }

    void Reset(int num_rows, int num_cols){
        if ( num_cols < 0 || num_rows < 0 )
            throw out_of_range("Reset to negative size attempt");
        if (num_cols == 0 || num_rows == 0)
            num_cols = num_rows = 0;
        mat_.assign(num_rows, vector<int> (num_cols, 0) );
    }

    int At(size_t row, size_t col) const {
        if ( col >= 0 && col < GetNumColumns() && row >= 0 && row < GetNumRows())
            return mat_[row][col];
        else
            throw out_of_range("Matrix size negative");
    };

    int& At(size_t row, size_t col) {
        if ( col >= 0 && col < GetNumColumns() && row >= 0 && row < GetNumRows())
            return mat_[row][col];
        else
            throw out_of_range("Matrix size negative");
    };


    size_t GetNumRows() const { return mat_.size();};
    size_t GetNumColumns() const {
        if (!mat_.empty()){
            return mat_.at(0).size();
        }
        else{
            return 0;
        }
    };

    bool operator==(const Matrix &rhs) const {
        return  (GetNumRows() == rhs.GetNumRows() && GetNumColumns() == rhs.GetNumColumns())
                ? mat_ == rhs.mat_
                : false ;
    }

    Matrix operator+(const Matrix &rhs) const{
        if (GetNumColumns() != rhs.GetNumColumns() || GetNumRows() != rhs.GetNumRows())
            throw invalid_argument("Matrixes have different size");

        Matrix mat_sum(GetNumRows(), GetNumColumns());
        for (size_t i = 0; i < GetNumRows(); ++i){
            for (size_t j = 0; j < GetNumColumns(); ++j){
                mat_sum.At(i, j) = At(i, j) + rhs.At(i, j);
            }
        }
        return mat_sum;
    }

};

istream& operator>>(istream& is, Matrix &mat){
    int cols, rows;
    is >> rows >> cols;
    mat.Reset(rows, cols);
    for (size_t i = 0; i < mat.GetNumRows(); ++i){
        for (size_t j = 0; j < mat.GetNumColumns(); ++j){
            is >> mat.At(i, j);
        }
    }
    return is;
}

ostream& operator<<(ostream& os, const Matrix &mat){
    os << mat.GetNumRows() << ' ' << mat.GetNumColumns() << endl;
    for (size_t i = 0; i < mat.GetNumRows(); ++i){
        for (size_t j = 0; j < mat.GetNumColumns(); ++j){
            os << mat.At(i, j);
            if ( j != mat.GetNumColumns() - 1)
                os << ' ';
        }
        os << endl;
    }
    return os;
}

int main() {

    Matrix one;
    Matrix two;
    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}


/*
in
3 5
6 4 -1 9 8
12 1 2 9 -5
-4 0 12 8 6

3 5
5 1 0 -8 23
14 5 -6 6 9
8 0 5 4 1

 out
 3 5
11 5 -1 1 31
26 6 -4 15 4
4 0 17 12 7
 * */
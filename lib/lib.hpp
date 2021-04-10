#include <iostream>
#include <vector>
using std::vector;

class Matrix {
public:
    Matrix(size_t size, std::vector<std::vector<int>> matrix): size_(size) {
        for (int i = 0; i < size; ++i) {
            matrix_[i] = matrix[i];
        }
    }

    Matrix(size_t size): size_(size), matrix_(size, vector<int>(size, 0)) {

    }

    size_t Size() const {
        return size_;
    }

    long long Det() {
        
    }

private:
    const size_t size_;
    vector<vector<int>> matrix_;
    friend std::ostream& operator<< (std::ostream &out, const Matrix &matrix);
    friend std::istream& operator>> (std::istream &in, Matrix &matrix);
};

std::ostream& operator<< (std::ostream &out, const Matrix &matrix) {
    for (int i = 0; i < matrix.Size(); ++i) {
        for (int j = 0; j < matrix.Size(); ++j)
            out << ' ' << matrix.matrix_[i][j];
        out << std::endl;
    }
    return out;
}

std::istream& operator>> (std::istream &in, Matrix &matrix) {
    for (int i = 0; i < matrix.Size(); ++i) {
        for (int j = 0; j < matrix.Size(); ++j)
            in >> matrix.matrix_[i][j];
    }
    return in;
}
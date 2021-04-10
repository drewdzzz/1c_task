#include <iostream>
#include <vector>
using std::vector;

class Matrix {
public:
    Matrix(size_t size, std::vector<std::vector<double>> matrix);

    Matrix(size_t size);

    Matrix();
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);

    size_t Size() const;

    double Det();

    Matrix GetMaxDetMatrix();

private:
    size_t size_;
    vector<vector<double>> matrix_;
    friend std::ostream& operator<< (std::ostream &out, const Matrix &matrix);
    friend std::istream& operator>> (std::istream &in, Matrix &matrix);
};
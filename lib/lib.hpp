#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

static const double EPSILON = 1e-6;

class Matrix {
public:
    Matrix(size_t size, std::vector<std::vector<double>> matrix): size_(size) {
        for (int i = 0; i < size; ++i) {
            matrix_[i] = matrix[i];
        }
    }

    Matrix(size_t size): size_(size), matrix_(size, vector<double>(size, 0)) {

    }

    Matrix(): size_(0){}
    Matrix(const Matrix& other): size_(other.size_), matrix_(other.matrix_) {
    }
    Matrix(Matrix&& other): size_(other.size_) {
        matrix_ = std::move(other.matrix_);
    }

    Matrix& operator=(const Matrix& other) {
        size_ = other.size_;
        matrix_ = other.matrix_;
        return *this;
    }
    Matrix& operator=(Matrix&& other) {
        matrix_ = std::move(other.matrix_);
        size_ = other.size_;
        return *this;
    }

    size_t Size() const {
        return size_;
    }

    double Det() {
        vector<vector<double>> tmp_matrix = matrix_;
        double det = 1;
        for (size_t i = 0; i < size_; ++i) {
            size_t k = i;
            for (size_t j = i + 1; j < size_; ++j) {
                if (abs(tmp_matrix[j][i]) > abs(tmp_matrix[k][i])) {
                    k = j;
                }
            }
            if (abs(tmp_matrix[k][i]) < EPSILON) {
                det = 0;
                break;
            }
            std::swap(tmp_matrix[i], tmp_matrix[k]);
            if (i != k) {
                det = -det;
            }
            det *= tmp_matrix[i][i];
            for (size_t j = i + 1; j < size_; ++j) {
                tmp_matrix[i][j] /= tmp_matrix[i][i];
            }
            for (size_t j = 0; j < size_; ++j) {
                if (j != i && abs (tmp_matrix [j][i]) > EPSILON) {
                    for (size_t k = i + 1; k < size_; ++k) {
                        tmp_matrix[j][k] -= tmp_matrix[i][k] * tmp_matrix[j][i];
                    }
                }
            }
        }
        return det;
    }

    Matrix GetMaxDetMatrix() {
        Matrix tmp_matrix(size_);
        Matrix max_det_matrix;
        double max_det = this->Det();

        vector<double> matrix_odd_place;
        vector<double> matrix_even_place;

        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                if ((i + j) % 2 == 0) {
                    matrix_even_place.push_back(matrix_[i][j]);
                } else {
                    matrix_odd_place.push_back(matrix_[i][j]);
                }
            }
        }
        std::sort(matrix_even_place.begin(), matrix_even_place.end());
        std::sort(matrix_odd_place.begin(), matrix_odd_place.end());

        do {
            do {
                size_t even_counter = 0;
                size_t odd_counter = 0;
                for (size_t i = 0; i < size_; ++i) {
                    for (size_t j = 0; j < size_; ++j) {
                        if ((i + j) % 2 == 0) {
                            tmp_matrix.matrix_[i][j] = matrix_even_place[even_counter++];
                        } else {
                            tmp_matrix.matrix_[i][j] = matrix_odd_place[odd_counter++];
                        }
                    }
                }
                double tmp_det = tmp_matrix.Det();
                if (tmp_det > max_det) {
                    max_det_matrix = tmp_matrix;
                    max_det = tmp_det;
                }
            } while(std::next_permutation(matrix_odd_place.begin(), matrix_odd_place.end()));
        } while(std::next_permutation(matrix_even_place.begin(), matrix_even_place.end()));
        return std::move(max_det_matrix);
    }

private:
    size_t size_;
    vector<vector<double>> matrix_;
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
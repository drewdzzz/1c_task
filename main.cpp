#include "lib/lib.hpp"

int main() {
    Matrix matrix(3);
    std::cin >> matrix;
    std::cout << "Input:" << std::endl;
    std::cout << matrix;
    std::cout << "Input det:" << std::endl;
    Matrix max_det_matrix = matrix.GetMaxDetMatrix();
    std::cout << "aaaaaaa" << std::endl;             //Крик души, простите
    std::cout << "Output:" <<std::endl;
    std::cout << max_det_matrix << std::endl;
    std::cout << "Output det:" << std::endl;
    std::cout << max_det_matrix.Det() << std::endl;
}
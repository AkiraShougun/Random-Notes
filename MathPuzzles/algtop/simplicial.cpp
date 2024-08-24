#include <iostream>
#include "Eigen/Dense"

int main()
{
    Eigen::Matrix<float, 2, 2> a;
    a << 2, 2, 2, 2;
    Eigen::FullPivLU<Eigen::Matrix<float, 2, 2>> lu_decomp(a);
    auto rank = lu_decomp.rank();
    std::cout << rank;
    return 0;
}

#include "gtest/gtest.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

// Let f(x) = x^2 + x + 1.
// We have the points f(-1)=1, f(0)=1 and f(1)=3.
// Given the points we want to find the [1,1,1] as the coefficients of the polynomial
TEST(EigenTests, BasicVandermondeTest) {
    MatrixXd m(3, 3);

    // Create the Vandermonde matrix
    m(0, 2) = 1.0;
    m(1, 2) = 1.0;
    m(2, 2) = 1.0;
    for (int i = 1; i >= 0; i--) {
        m(0, i) = m(0, i+1) * -1;
        m(1, i) = m(1, i+1) * 0;
        m(2, i) = m(2, i+1) * 1;
    }

    VectorXd b(3);
    b(0) = 1.0;
    b(1) = 1.0;
    b(2) = 3.0;

    // Solve for the coefficients of the polynomial
    VectorXd x = m.partialPivLu().solve(b);
   
    ASSERT_DOUBLE_EQ(1.0, x(0));
    ASSERT_DOUBLE_EQ(1.0, x(1));
    ASSERT_DOUBLE_EQ(1.0, x(2));
}
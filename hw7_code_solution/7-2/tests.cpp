#include <iostream>

// Your code must compile.
#include "rational.hpp"
#include "rational.hpp"
#include "matrix.hpp"
#include "matrix.hpp"

using namespace std;

void TestDouble()
{
    Matrix<double> matrix(3, 4);
    matrix(0, 0) = 0;    matrix(0, 1) = 0.4;  matrix(0, 2) = 0.2;  matrix(0, 3) = 0.6;
    matrix(1, 0) = 0.2;  matrix(1, 1) = 0.2;  matrix(1, 2) = 0.2;  matrix(1, 3) = 0.8;
    matrix(2, 0) = -0.6; matrix(2, 1) = 0;    matrix(2, 2) = 0.2;  matrix(2, 3) = 1;

    matrix.Print();
    /*  0 0.4 0.2 0.6
        0.2 0.2 0.2 0.8
        -0.6 0 0.2 1    */
    std::cout << std::endl;
    matrix.GaussJordan();
    matrix.Print();
    /*  0.2 0.2 0.2 0.8
        0 0.6 0.8 3.4
        0 0 -0.333333 -1.66667   */
}

void TestRational()
{
    Matrix<Rational> matrix(3, 4);
    matrix(0, 0) = 0;               matrix(0, 1) = Rational(2, 5);   matrix(0, 2) = Rational(1, 5);   matrix(0, 3) = Rational(3, 5);
    matrix(1, 0) = Rational(1, 5);  matrix(1, 1) = Rational(1, 5);   matrix(1, 2) = Rational(1, 5);   matrix(1, 3) = Rational(4, 5);
    matrix(2, 0) = Rational(-3, 5); matrix(2, 1) = Rational(0, 5);   matrix(2, 2) = Rational(1, 5);   matrix(2, 3) = Rational(1);
    
    matrix.Print();
    /*  0 2/5 1/5 3/5
        1/5 1/5 1/5 4/5
        -3/5 0 1/5 1    */
    std::cout << std::endl;
    matrix.GaussJordan();
    matrix.Print();
    /*  1/5 1/5 1/5 4/5
        0 3/5 4/5 17/5
        0 0 -1/3 -5/3    */
}

int main()
{
    TestDouble();
    TestRational();
}


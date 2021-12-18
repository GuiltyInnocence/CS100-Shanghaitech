#include <iostream>

// Your code must compile.
#include "rational.hpp"
#include "rational.hpp"


using namespace std;

int main()
{
    Rational a(-6, 10);
    Rational b(1, 7);
    cout << a << " " << a+b << " " << b-a << " " << b/a << endl;
    // -3/5 -16/35 26/35 -5/21
}


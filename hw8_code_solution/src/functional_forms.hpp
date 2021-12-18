#ifndef FUNCTIONAL_FORMS_HPP_
#define FUNCTIONAL_FORMS_HPP_

#include <stdlib.h>
#include <math.h>

/* For all lambda functions below, if you are not clear how they work, please refer to the given example for details. */

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1+f2)(m) as first, and (d(f1+f2)/dx)(m) as second.
 */
auto derSum = []( auto f1, auto f2 ){
    return [=](auto m){
        return std::make_pair(
                f1(m).first+f2(m).first,
                f1(m).second+f2(m).second
                );
    };
  //add your code here ...
};


/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1-f2)(m) as first, and (d(f1-f2)/dx)(m) as second.
 */
auto derSub = []( auto f1, auto f2 ){
    return [=](auto m){
        return std::make_pair(
                f1(m).first-f2(m).first,
                f1(m).second-f2(m).second
                );
    };
  //add your code here ...
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1*f2)(m) as first, and (d(f1*f2)/dx)(m) as second.
 */
auto derMul = []( auto f1, auto f2 ){
    return [=](auto m){
        return std::make_pair(
                f1(m).first*f2(m).first,
                f1(m).second*f2(m).first+f1(m).first*f2(m).second
                );
    };
  //add your code here ...
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1/f2)(m) as first, and (d(f1/f2)/dx)(m) as second.
 */
auto derDiv = []( auto f1, auto f2 ){
    return [=](auto m){
        return std::make_pair(
                f1(m).first/f2(m).first,
                (f1(m).second*f2(m).first-f1(m).first*f2(m).second)/(f2(m).first*f2(m).first)
                );
    };
  //add your code here ...
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f2(f1))(m) as first, and (d(f2(f1))/dx)(m) as second.
 */
auto derComp = []( auto f1, auto f2 ){
    return [=](auto m){
        return std::make_pair(
                f2(f1(m).first).first,
                f2(f1(m).first).second*f1(m).second
                );
    };
  //add your code here ...
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has [(f1)(m)]^exp as first, and (d(f1^exp)/dx)(m) as second.
 */
auto derPow = []( auto f, int exp ) {
    return [=](auto m){
        return std::make_pair(
                pow(f(m).first,exp),
                exp*pow(f(m).first,exp-1)*f(m).second
                );
    };
  //add your code here ...
};

#endif
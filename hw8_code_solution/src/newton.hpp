#ifndef NEWTON_HPP_
#define NEWTON_HPP_

#include <stdlib.h>

template<typename T>
double findNearestRoot( T f, double startingPoint, double eps = 0.000001 ) {
    // add your code here ...
    double now=startingPoint;
    while(fabs(f(now).first)>eps)
        now-=f(now).first/f(now).second;
    return now;
}

#endif
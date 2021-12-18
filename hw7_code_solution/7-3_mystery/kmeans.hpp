#ifndef __CS100_KMEANS_HPP_
#define __CS100_KMEANS_HPP_

#include <iostream>
#include <vector>
#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include <cassert>
//
//#define NDEBUG

#define THREAD 4
#define eps 1e-5


using index_t = int;

struct Point
{
    double x, y;

    Point() : x(0), y(0) {};
    Point(double x_, double y_) : x(x_), y(y_) {}
    Point(const Point& other) : x(other.x), y(other.y) {}
    double sDistance(Point& other) const;
};


class Kmeans
{
public:
    Kmeans(const std::vector<Point>& points, const std::vector<Point>& initialCenters);
    std::vector<index_t> Run(int maxIterations=1000);

private:
    std::vector<Point> m_points;
    std::vector<Point> m_centers;
    int m_numPoints;
    int m_numCenters;
};

std::istream& operator>>(std::istream& is, Point& pt);
std::ostream& operator<<(std::ostream& os, Point& pt);


void assigncenterNG(std::vector<index_t>& assignment,int xi,int m_numPoints,int m_numCenters,std::vector<Point>& m_points,std::vector<Point>& m_centers);


#endif // __KMEANS_HPP_
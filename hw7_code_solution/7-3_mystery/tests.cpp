#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "kmeans.hpp"
#include "kmeans.cpp"

int main(){
    std::ifstream ifs;
    ifs.open("input.txt");

    int numPoints, numCenters;
    ifs >> numPoints >> numCenters;

    std::vector<Point> points(numPoints);
    std::vector<Point> centers(numCenters);
    for (int i = 0; i < numCenters; i++)
        ifs >> centers[i];
    for (int i = 0; i < numPoints; i++)
        ifs >> points[i];

    std::ofstream ofs;
    ofs.open("ninput.txt");

    ofs<<numPoints<<' '<<numCenters<<'\n';
    srand(unsigned(time(NULL)));
    int par[15]={23555,10001,123,6197,114514,66666,0,77,44444,99999,30157,123456,75558,192608,101010};
    for(int j=0;j<numCenters;j++){
        ofs<<std::setprecision(15)<<points[par[j]]<<'\n';
    }
    for(int i=0;i<numPoints;i++)
        ofs<<points[i]<<'\n';
    ifs.close();
    ofs.close();
    return 0;
}



// ==================================
// IMPORTANT: DO NOT MODIFY THIS FILE
// ==================================
#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include <fstream>

#include "kmeans.hpp"


using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

int main()
{
    /*
    if (argc != 2)
    {
        std::cout << "Usage: ./kmeans <output_file.txt>";
        return 1;
    }*/
    ///
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

    std::shared_ptr<Kmeans> problem(new Kmeans(points, centers));

    auto start = high_resolution_clock::now();
    auto result = problem->Run();
    auto end = high_resolution_clock::now();
    std::cout << "Time cost: " << (double)duration_cast<microseconds>(end - start).count() / 1000000.0 << "s" << std::endl;

    std::cout << "Writing output files..." << std::endl;
    std::ofstream ofs;
    ofs.open("out.txt");
    for (int i = 0; i < numPoints; i++)
        ofs << points[i] << " " << result[i] << std::endl;
    ofs.close();
    return 0;
}
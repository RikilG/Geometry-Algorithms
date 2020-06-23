/**
 * \file main.cpp
 * \brief Main file which takes input, computes convex hull and returns output
 * 
 * This is the main runner file which uses the convexHull() function from the header
 * ConvexHull.h to compute the convex hull. This file also uses std::chrono from the 
 * chrono c++ header to estimate the duration of the convex hull computation
 */

#include <chrono>
#include "Tools.h"
#include "ConvexHull.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    // start timer
    auto start = high_resolution_clock::now();

    // read points from file or stdin
    PointList input = readPoints(argc, argv);
    auto lap1 = high_resolution_clock::now();

    // generate convex hull
    PointList output = convexHull(input);
    auto lap2 = high_resolution_clock::now();
    
    // Print output points
    for (const Point &p: output)
        cout << p << "\n";

    // Print time analysis
    auto input_time = duration_cast<milliseconds>(lap1 - start);
    auto run_time = duration_cast<milliseconds>(lap2 - lap1);
    cout << "Time taken for input: " << input_time.count() << "\n";
    cout << "Time taken for computing convex hull: " << run_time.count() << "\n";
    return 0;
}
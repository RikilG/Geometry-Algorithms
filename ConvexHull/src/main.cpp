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
    cout << "Number of points on convex hull: " << output.size() << "\n";

    // Print time analysis
    auto input_time = duration_cast<microseconds>(lap1 - start);
    auto run_time = duration_cast<microseconds>(lap2 - lap1);
    cout << "Time taken for input: " << input_time.count() << "\n";
    cout << "Time taken for computing convex hull: " << run_time.count() << "\n";
    return 0;
}


//      THIS IS THE MAIN PAGE OF DOCUMENTATION.
/**
 * \mainpage
 * 
 * \section Algorithm
 * This algorithm deals with finding convex hull over the points given in the input. <br>
 * <b>How it works</b><br>
 * A simple overview of the algorithm: <br>
 * Step 1: Recursively compute the upper hull <br>
 * Step 2: Recursively compute the lower hull <br>
 * Step 3: Combine both the hulls and return the output <br>
 * 
 * *********************************** 
 * Steps to Compile and Run : <br>
 * 1) <em>cd</em> into the src directory <br>
 * 2) Run <em>g++ main.cpp</em> which generates an executable called <em>a.out</em> in the same directory <br>
 * 3) Run the executable using <em>./a.out</em> (on linux) <br>
 *    3.1) The executable takes a dataset from command line argument. For example, to use an existing dataset, run <em>./a.out ../datasets/edge.txt</em> <br>
 *    3.2) If no command-line argument is given, it takes input from the shell directly (stdin) <br>
 * 
 * <br> Performance of the algorithm is documented in the report<br>
 * 
 * \subsection Input
 * 
 * Input is given as follows:<br>
 *  - Input can be given both from file (via command-line args) or stdin <br>
 *  - First line must contain the no of Points to be taken as input by the program. <br>
 *  - Each of next line must contain 2 integers, space seperated denoting the (x, y) coordinates of each point. <br>
 *  - Each coordinate must be of integer type in the range -10^6 to 10^6. <br>
 *  - Number of coordinates must be less than 1 Billion. <br>
 * 
 * \subsection Output
 *  - Each line of output gives the coordinates present on the convex hull in clockwise order
 * 
 * <hr>
 * \subsection Author
 * The algorithm is implemented and documented by <b>Rikil Gajarla (2017A7PS0202H)</b>.
 * <hr>
 * 
 */
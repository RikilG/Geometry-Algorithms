/**
 * @file main.cpp
 * @author Rikil Gajarla (f20170202@hyderabad.bits-pilani.ac.in)
 * @brief The main runner program to take input, triangulate and provide output
 * 
 */

#include <iostream>
#include <vector>
#include <chrono>

#include "Geometry.h"
#include "Tools.h"
#include "earClippingTriangulation.h"
#include "planeSweepTriangulation.h"

using namespace std;
using namespace std::chrono;

/**
 * @brief main function which starts the execution of the triangulation program
 * 
 * @param argc No of command line arguments proveided by the os
 * @param argv Command line arguments given by the user, supplied by the os
 * @return int 0 if program exits successfully
 */
int main(int argc, char *argv[]) {
    // start timer
    auto start = high_resolution_clock::now();

    // read input
    vector<Vertex> input = readvertices(argc, argv);
    auto lap1 = high_resolution_clock::now();

    // perform triangulation with any of the below algorithms
    // vector<Triangle> output = earClippingTriangulate(input);
    vector<Triangle> output = planeSweepTriangulate(input);
    auto lap2 = high_resolution_clock::now();

    // print output
    for (Triangle &t: output) {
        cout << t << "\n";
    }
    cout << "No of triangles: " << output.size() << "\n";

    // Print time analysis
    auto input_time = duration_cast<microseconds>(lap1 - start);
    auto run_time = duration_cast<microseconds>(lap2 - lap1);
    cout << "\nTime taken for input: " << input_time.count() << "\n";
    cout << "Time taken for Triangulating: " << run_time.count() << "\n";
    return 0;
}


//      THIS IS THE MAIN PAGE OF DOCUMENTATION.
/**
 * \mainpage
 * 
 * \section Overview
 * This program deals with triangulation of polygons. <br>
 * <b>How it works</b><br>
 * A simple overview of the triangulation process: <br>
 * Step 1: Subdivide the input polygon into monotones by drawing diagonals in the polygon. <br>
 * Step 2: For each monotone, perform Monotone triangulation which can be easily done. <br>
 * Step 3: Combine the output of all monotone triangulations to get the final triangulation for the polygon <br>
 * <br>
 * The ear clipping algorithm is even more simpler, but is not efficient w.r.t time complexity: <br>
 * Step 1: Find the "ear" of the polygon. which is the vertex whose internal angle is less than PI <br>
 * Step 2: Check if any other Reflex Vertex (whose internal angel is greater than PI) comes under the triangle to be formed. If 
 * so, then repeat Step 1 until a valid "ear" can be found. It is proved that there are always atleast 2 ears for any vertex
 * hence, it is sure that we will find it. <br>
 * Step 3: Triangulate this ear by drawing a diagonal on the adjacent vertices to this vertex, store this operation/triangle
 * and remove the ear vertex from the polygon. loop from step 1 until we triangulate completely.<br>
 * 
 * *********************************** 
 * Steps to Compile and Run : <br>
 * 1) <em>cd</em> into the src directory <br>
 * 2) Run <em>g++ main.cpp</em> which generates an executable called <em>a.out</em> in the same directory <br>
 * 3) Run the executable using <em>./a.out</em> (on linux) <br>
 *    3.1) The executable takes a dataset from command line argument. For example, to use an existing dataset, run <em>./a.out ../datasets/1sq.txt</em> <br>
 *    3.2) If no command-line argument is given, it takes input from the shell directly (stdin) <br>
 * 
 * <br> Performance of the algorithm is documented in the report<br>
 * 
 * \subsection Input
 * 
 * Input is given as follows:<br>
 *  - Input can be given both from file (via command-line args) or stdin <br>
 *  - Input <b>must</b> contain the clockwise ordering of input vertices
 *  - First line must contain the no of Points to be taken as input by the program. <br>
 *  - Each of next line must contain 2 integers, space seperated denoting the (x, y) coordinates of each point. <br>
 *  - Each coordinate must be of integer type in the range -10^8 to 10^8. <br>
 *  - Number of coordinates must be less than 1 Billion. <br>
 * 
 * \subsection Output
 *  - The output contains the coordinates of all the triangles formed after triangulation of the polygon.<br>
 * 
 * <hr>
 * \subsection Author
 * The algorithm is implemented and documented by <b>Rikil Gajarla (2017A7PS0202H)</b>.
 * <hr>
 * 
 */
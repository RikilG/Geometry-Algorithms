/**
 * @file main.cpp
 * @author Rikil Gajarla (f20170202@hyderabad.bits-pilani.ac.in)
 * @brief This file is the main runner function which initializes the DCEL
 */

#include <vector>
#include <chrono>
#include <iostream>
#include "DCEL.h"
#include "Tools.h"

using namespace std;
using namespace std::chrono;

/**
 * @brief main runner function to run DCEL
 * 
 * @param argc number of command line arguments, supplied by os
 * @param argv command line arguments given by the user, supplied by the os
 * @return int returns 0 on successful execution
 */
int main(int argc, char *argv[]) {
    // start timer
    auto start = high_resolution_clock::now();
    
    // read points from input
    vector<Edge> inputEdges = readEdges(argc, argv);
    auto lap1 = high_resolution_clock::now();

    // build dcel structure
    DCEL dcel = DCEL(inputEdges);
    auto lap2 = high_resolution_clock::now();

    // Vertex *a = dcel.getVertex(Vertex(0, 0));
    // Vertex *b = dcel.getVertex(Vertex(1, 1));
    // dcel.addEdge(a, b);

    // print DECL
    // for (Vertex* v: dcel.vertices) {
    //     vector<HalfEdge*> helist = dcel.heMap[v];
    //     for (HalfEdge* he: helist) {
    //         cout << *he << ", Face: " << he->face->id << "\n";
    //     }
    //     cout << "\n";
    // }
    for (Face *f: dcel.faces) {
        cout << *f << "\n";
        dcel.printBoundaryEdges(f);
    }

    // Print DCEL order of geometry
    cout << "\n";
    cout << "Number of Vertices: " << dcel.vertices.size() << "\n";
    cout << "Number of Edges: " << inputEdges.size() << "\n";
    cout << "Number of Faces: " << dcel.faces.size() << "\n\n";

    // Print time analysis
    auto input_time = duration_cast<microseconds>(lap1 - start);
    auto run_time = duration_cast<microseconds>(lap2 - lap1);
    cout << "Time taken for input: " << input_time.count() << " microsec\n";
    cout << "Time taken for building DCEL: " << run_time.count() << " microsec\n";
    return 0;
}


//      THIS IS THE MAIN PAGE OF DOCUMENTATION.
/**
 * \mainpage
 * 
 * \section Overview
 * This program deals with building a DCEL data strutcure to store any type of planar graph given in the input. <br>
 * <b>How it works</b><br>
 * A simple overview of the construction of DCEL: <br>
 * Step 1: For each Edge, create two new HalfEdges, assign their twins and put them in corresponding source/tail vertex lists <br>
 * Step 2: Sort all the HalfEdges present at each Vertex in clockwise order <br>
 * Step 3: For Every pair of HalfEdges next to each other on a Vertex, assign their next and prev pointers <br>
 * Step 4: Taking each HalfEdge, if its face points to nullptr, create new face and assign to all HalfEdges which can
 * be obtained by traversing the next pointer. Set the represntative of Face object to any of theese halfedges and add 
 * this face to the list of Faces present in the DCEL <br>
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
 *  - First line must contain the no of Edges to be taken as input by the program. <br>
 *  - Each of next line must contain 4 integers, space seperated denoting the (x1, y1), (x2, y2) coordinates of endpoints of each edge. <br>
 *  - Each coordinate must be of integer type in the range -10^8 to 10^8. <br>
 *  - Number of coordinates must be less than 1 Billion. <br>
 * 
 * \subsection Output
 *  - The program prints all the Faces, Edges, HalfEdges which are incident and present in the DCEL structure to accurately show the representation of planar graph
 * 
 * <hr>
 * \subsection Author
 * The algorithm is implemented and documented by <b>Rikil Gajarla (2017A7PS0202H)</b>.
 * <hr>
 * 
 */
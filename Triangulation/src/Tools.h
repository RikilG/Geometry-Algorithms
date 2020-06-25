/**
 * \file Tools.h
 * \brief The main purpose of this file is to provide a data input function.
 * 
 * This file provides the readPoints() function which helps to read file and 
 * take input from it. In case any file is not provided, It tries to take input
 * from the user via stdin. some other functions like det(), dist(), and other
 * triangle related helper functions are also present
 */

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include "Geometry.h"

using namespace std;

/**
 * @brief Compute the determinant of the given triangle or the cross product to the given vectors
 * 
 * @param u First Vertex type object
 * @param v Second Vertex type object
 * @return double determinant or cross product
 */
double det(const Vertex &u, const Vertex &v) { // cross
    return u.x*(double)v.y - u.y*(double)v.x;
}

/**
 * @brief Compute the distance between given points
 * 
 * @param u First Vertex
 * @param v Second Vertex
 * @return double distance between the Vertex objects
 */
double dist(Vertex const &u, Vertex const &v) {
    return sqrt(pow((v.x - u.x), 2) + pow((v.y - u.y), 2));
}

/**
 * \brief To check the orientation of the given 3 points
 * \param p Point object
 * \param q Point object
 * \param r Point object
 * \return Orientation: -1 if clockwise, +1 if counter-clockwise and 0 if colinear
 */
int orient(const Vertex &p, const Vertex &q, const Vertex &r) {
    // counter clock wise: +ve: upward direction: +ve orient
    double x = ((q.x*(double)r.y-r.x*(double)q.y) - p.x*(double)(r.y-q.y) + p.y*(double)(r.x-q.x));
    // if (x == 0) return 0;
    if (abs(x) < epsillion) return 0;
    else return (x>0) ? 1 : -1 ;
}

/**
 * @brief Check if a point is present in the triangle
 * 
 * @param a First Vertex of the triangle
 * @param b Second Vertex of the triangle
 * @param c Third Vertex of the triangle
 * @param p Vertex/Point to be checked if it lies inside the triangle
 * @return true if the point lies inside the triangle
 * @return false if the point does not lie inside the triangle
 */
bool pointInTriangle(Vertex a, Vertex b, Vertex c, Vertex p) {
    // check if point p is within the triangle abc: the point must be at the left
    // of each edge
    Vertex ab = b - a;
    Vertex bc = c - b;
    Vertex ca = a - c;

    if (orient(a, b, p) < 0 && orient(b, c, p) < 0 && orient(c, a, p) < 0)
        return true;
    else 
        return false;

    if (det(ab, p - a) > 0 && det(bc, p - b) > 0 && det(ca, p - c) > 0)
        return true;
    else
        return false;
}

void log(string s) {
    cout << s << "\n";
}

/**
 * \brief Read input vertices from stdin or from file (if provided in args)
 * \param argc no of command-line arguments
 * \param argv command-line arguments
 * \return vector<Vertex> object containing the input points in the given order
 */
vector<Vertex> readvertices(int argc, char *argv[]) {
    string current_exec_name = argv[0]; // Name of the current exec program
    vector<string> all_args;
    vector<Vertex> vertices;
    ifstream myFile;
    stringstream ss;
    string line;
    float a, b;
    if (argc > 1) { // convert args to string from char*
        all_args.assign(argv + 1, argv + argc);
    }

    if (argc > 1 && all_args[0] == "help") { // asking help
        cout << "Polygon Triangulation Program.\n"
            << "Input: file with space seperated vertices as command line argument.\n"
            << "Output: each line consisting of triangle vertices\n"
            << "\nFile format: first line n = number of vertices\n"
            << "next n lines each having space seperated integer coordinates of polygon vertices listed in clockwise order on polygon\n";
        exit(0);
    }
    else if (argc == 1) { // no args
        cout << "Manual input (File not specified in args)\n";
        cout << "Enter no of vertices: ";
        long n; cin >> n;
        cout << "Enter vertices as space seperated coordinates in each line\n";
        for (long long i=0;i<n;i++) {
            cin >> a >> b;
            vertices.emplace_back(a, b, i);
        }
    }
    else if (argc != 2) { // incorrect args
        cout << "Only one file name is taken as argument.\n"
            << "Type 'help' as arg to know more." << endl;
        exit(0);
    }
    else { // file operation
      myFile.open(all_args[0]);
      cout << "Opening: " << all_args[0] << "\n";
      if (myFile.is_open()) {
        long long n;
        getline(myFile, line);
        ss << line;
        ss >> n;
        for (long long i = 0; i < n; i++) {
          getline(myFile, line);
          ss.clear();
          ss << line;
          ss >> a >> b;
          vertices.emplace_back(a, b, i);
        }
      } else {
        cout << "Error opening file. please check and try again." << endl;
        exit(0);
      }
      myFile.close();
    }
    return vertices;
}

#endif

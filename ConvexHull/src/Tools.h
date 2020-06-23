/**
 * \file Tools.h
 * \brief The main purpose of this file is to provide a data input function.
 * 
 * This file provides the readPoints() function which helps to read file and 
 * take input from it. In case any file is not provided, It tries to take input
 * from the user via stdin.
 */

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <vector>
#include <fstream>
#include <sstream>
#include "Point.h"
#include "PointList.h"

using namespace std;

/**
 * \brief To check the orientation of the given 3 points
 * \param p Point object
 * \param q Point object
 * \param r Point object
 * \return Orientation: -1 if clockwise, +1 if counter-clockwise and 0 if colinear
 */
int orient(const Point &p, const Point &q, const Point &r) {
    // counter clock wise: +ve: upward direction: +ve orient
    long long x = ((q.x*(long long)r.y-r.x*(long long)q.y) - p.x*(long long)(r.y-q.y) + p.y*(long long)(r.x-q.x));
    if (x == 0) return 0;
    else return (x>0) ? 1 : -1 ;
}

void log(string s) {
    cout << s << "\n";
}

/**
 * \brief Read input points from stdin or from file (if provided in args)
 * \param argc no of command-line arguments
 * \param argv command-line arguments
 * \return PointList object containing the input points in the given order
 */
PointList readPoints(int argc, char *argv[]) {
    string current_exec_name = argv[0]; // Name of the current exec program
    vector<string> all_args;
    PointList points;
    ifstream myfile;
    stringstream ss;
    string line;
    long a, b;
    if (argc > 1) { // convert args to string from char*
        all_args.assign(argv + 1, argv + argc);
    }

    if (argc > 1 && all_args[0] == "help") { // asking help
        cout << "Convex hull generator program.\n"
            << "Input: file with space seperated points as command line argument.\n"
            << "Output: Counter clockwise order of points on Convex hull written to stdout.\n";
        exit(0);
    }
    else if (argc == 1) { // no args
        cout << "Manual input: File not specified in args.\n";
        cout << "Enter no of points: ";
        long n; cin >> n;
        cout << "Enter points as space seperated cordinates in each line\n";
        for (long i=0;i<n;i++) {
            cin >> a >> b;
            points.emplace_back(a, b);
        }
    }
    else if (argc != 2) { // incorrect args
        cout << "Only one file name is taken as argument.\n"
            << "Type 'help' as arg to know more." << endl;
        exit(0);
    }
    else { // file operation
        myfile.open(all_args[0]);
        cout << "Opening: " << all_args[0] << "\n";
        if (myfile.is_open()) {
            long long n;
            getline(myfile, line);
            ss << line;
            ss >> n;
            for (long long i=0;i<n;i++) {
                getline(myfile, line);
                ss.clear();
                ss << line;
                ss >> a >> b;
                points.emplace_back(a, b);
            }
        }
        else {
            cout << red+"Error opening file. please check and try again."+reset << endl;
            exit(0);
        }
        myfile.close();
    }
    return points;
}

#endif
#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <vector>
#include <fstream>
#include <sstream>
#include "Point.h"
#include "PointList.h"

using namespace std;

int orient(const Point &p, const Point &q, const Point &r) {
    // counter clock wise: +ve: upward direction: +ve orient
    int x = ((q.x*r.y-r.x*q.y) - p.x*(r.y-q.y) + p.y*(r.x-q.x));
    if (x == 0) return 0;
    else return (x>0) ? 1 : -1 ;
}

void log(string s) {
    cout << s << "\n";
}

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
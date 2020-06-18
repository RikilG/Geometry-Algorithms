#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "DCEL.h"

using namespace std;

int orient(const Vertex &p, const Vertex &q, const Vertex &r) {
    // counter clock wise: +ve: upward direction: +ve orient
    int x = ((q.x*r.y-r.x*q.y) - p.x*(r.y-q.y) + p.y*(r.x-q.x));
    if (x == 0) return 0;
    else return (x>0) ? 1 : -1 ;
}

void log(string s) {
    cout << s << "\n";
}

vector<Edge> readEdges(int argc, char *argv[]) {
    string current_exec_name = argv[0]; // Name of the current exec program
    vector<string> all_args;
    vector<Edge> edges;
    ifstream myFile;
    stringstream ss;
    string line;
    long a, b, c, d;
    if (argc > 1) { // convert args to string from char*
        all_args.assign(argv + 1, argv + argc);
    }

    if (argc > 1 && all_args[0] == "help") { // asking help
        cout << "KirkPatrick Planar Point Location Program\n"
            << "Input: filename as command line argument.\n"
            << "Output: face number, one incident edge and vertex of the corresponding face\n"
            << "\nFile Format:\n"
            << "first line: no of edges"
            << "next, each line representing 4 integer coordinates (space seperated):\n"
            << "x1 y1 x2 y2\n where it represents edge existing between (x1,y1) and (x2,y2)\n";
        exit(0);
    }
    else if (argc == 1) { // no args
        cout << "Manual input: File not specified in args.\n";
        cout << "Enter no of edges: ";
        unsigned long n; cin >> n;
        cout << "Enter vertices of each edge as space seperated coordinates in each line: x1 y1 x2 y2\n";
        for (long i=0;i<n;i++) {
            cin >> a >> b >> c >> d;
            edges.emplace_back(a, b, c, d);
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
          ss >> a >> b >> c >> d;
          edges.emplace_back(a, b, c, d);
        }
      } else {
        cout << "Error opening file. please check and try again." << endl;
        exit(0);
      }
      myFile.close();
    }
    return edges;
}

#endif

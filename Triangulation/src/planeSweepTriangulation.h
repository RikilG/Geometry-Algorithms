/**
 * @file planeSweepTriangulation.h
 * @author Rikil Gajarla (f20170202@hyderabad.bits-pilani.ac.in)
 * @brief This file provides the wrapper function to monotone triangulate a polygon
 * 
 */

#ifndef __PLANESWEEPTRIANGULATION_H__
#define __PLANESWEEPTRIANGULATION_H__

#include <list>
#include <vector>
#include "Geometry.h"
#include "monotoneSubdivision.h"
#include "monotoneTriangulation.h"

using namespace std;

/**
 * @brief The wrapper method to monotone triangulate a polygon
 * 
 * This function internally calls getMonotones() and monotoneTriangulate() 
 * functions to get the triangulations
 * 
 * @param input List of Vertices of Polygons present in clockwise order
 * @return vector<Triangle> List of Triangle objects representing the triangulation of polygon
 */
vector<Triangle> planeSweepTriangulate(vector<Vertex> input) {
    vector<Triangle> output;
    list<vector<Vertex>> monotones = getMonotones(input);
    // cout << "no of monotones: " << monotones.size() << "\n";
    // for (auto &monotone: monotones) {
    //     for (auto &x: monotone) {
    //         cout << x << " ";
    //     }cout << "\n";
    // }
    // exit(1);
    for (auto &monotone: monotones) {
        vector<Triangle> temp = monotoneTriangulate(monotone);
        output.insert(output.end(), temp.begin(), temp.end());
    }
    return output;
}

#endif

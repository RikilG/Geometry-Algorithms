#ifndef __PLANESWEEPTRIANGULATION_H__
#define __PLANESWEEPTRIANGULATION_H__

#include <list>
#include <vector>
#include "Geometry.h"
#include "monotoneSubdivision.h"
#include "monotoneTriangulation.h"

using namespace std;

vector<Triangle> planeSweepTriangulate(vector<Vertex> input) {
    vector<Triangle> output;
    list<vector<Vertex>> monotones = getMonotones(input);
    for (auto &monotone: monotones) {
        vector<Triangle> temp = monotoneTriangulate(monotone);
        output.insert(output.end(), temp.begin(), temp.end());
    }
    return output;
}

#endif

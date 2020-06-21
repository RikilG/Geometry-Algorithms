#include <iostream>
#include <vector>

#include "Geometry.h"
#include "Tools.h"
#include "earClippingTriangulation.h"
#include "planeSweepTriangulation.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<Vertex> input = readvertices(argc, argv);
    // vector<Triangle> output = earClippingTriangulate(input);
    vector<Triangle> output = planeSweepTriangulate(input);
    cout << "No of triangles: " << output.size() << "\n";
    for (Triangle &t: output) {
        cout << t << "\n";
    }
    return 0;
}

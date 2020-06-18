#include <iostream>
#include <vector>
#include "Geometry.h"
#include "Tools.h"
#include "earClipping.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<Vertex> input = readvertices(argc, argv);
    vector<Triangle> output = triangulate(input);
    return 0;
}

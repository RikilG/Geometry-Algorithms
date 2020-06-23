#include <bits/stdc++.h>
#include "DCEL.h"
#include "Tools.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<Edge> inputEdges = readEdges(argc, argv);
    DCEL dcel = DCEL(inputEdges);
    Vertex *a = dcel.getVertex(Vertex(0, 0));
    Vertex *b = dcel.getVertex(Vertex(1, 1));
    dcel.addEdge(a, b);
    // test DECL
    // for (Vertex* v: dcel.vertices) {
    //     vector<HalfEdge*> helist = dcel.heMap[v];
    //     for (HalfEdge* he: helist) {
    //         cout << *he << ", Face: " << he->face->id << "\n";
    //     }
    //     cout << "\n";
    // }
    // for (Face *f: dcel.faces) {
    //     cout << *f << "\n";
    // }
    return 0;
}

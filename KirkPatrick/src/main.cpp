#include <bits/stdc++.h>
#include "DCEL.h"
#include "Tools.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<Edge> inputEdges = readEdges(argc, argv);
    DCEL dcel = DCEL(inputEdges);
    // test DECL
    // for (Vertex* v: dcel.vertices) {
    //     vector<HalfEdge*> helist = dcel.heMap[v];
    //     for (HalfEdge* he: helist) {
    //         printf("(%ld, %ld)->(%ld,%ld)\n", he->tail->x, he->tail->y, he->head->x, he->head->y);
    //     }
    //     cout << "\n";
    // }
    // for (Face *f: dcel.faces) {
    //     cout << "Face id: " << f->id << "\n";
    // }
    return 0;
}

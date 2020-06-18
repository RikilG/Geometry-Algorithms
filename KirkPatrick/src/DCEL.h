#ifndef __DCEL_H__
#define __DCEL_H__

#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <algorithm>

#include "Geometry.h"

using namespace std;

bool compare(const HalfEdge *p, const HalfEdge *q) { // needs revision
    const Vertex *a = p->head, *b = q->head;
    const Vertex *o = p->tail;
    return atan2(a->y - o->y, a->x - o->x) > atan2(b->y - o->y, b->x - o->x);
/*
    if (a->y*(long long)b->y <= 0) // If a & b have diff signs on their y coordinate?
        return a->y < b->y || (a->y == b->y && a->x < b->x); // Then the one pointing down comes before. If both have y = 0, then test x coord.
    else // Same y signs, establish ordering with a perpdot b.
        return (a->x*(long long)b->y - a->y*(long long)b->x) < 0; 
*/
}

class DCEL {
    private:
        Vertex* inSet(Vertex &a) {
            for (auto &v: vertices)
                if (v->x == a.x && v->y == a.y) return v;
            return nullptr;
        }
    public:
        map<Vertex *, vector<HalfEdge *>> heMap;
        vector<Vertex *> vertices;
        vector<Face *> faces;
        DCEL(vector<Edge> &edgelist) {
            // For each edge,
            // Add half edge to the vertex list of its source
            for (Edge &edge: edgelist) {
                Vertex *a = inSet(edge.src);
                Vertex *b = inSet(edge.dst);
                if (a == nullptr) {
                    a = new Vertex(edge.src);   
                    heMap[a] = vector<HalfEdge *>{};
                    vertices.push_back(a);
                }
                if (b == nullptr) {
                    b = new Vertex(edge.dst);
                    heMap[b] = vector<HalfEdge *>{};
                    vertices.push_back(b);
                }
                HalfEdge *e12 = new HalfEdge(a, b);
                HalfEdge *e21 = new HalfEdge(b, a);
                e12->twin = e21;
                e21->twin = e12;
                heMap[a].emplace_back(e12);
                heMap[b].emplace_back(e21);
            }
            // Sort each vertices half-edge list in clockwise order
            for (auto &x : heMap) {
                sort(x.second.begin(), x.second.end(), compare);
            }
            // assign next and prev of each half edge
            // for every pair of half-edges e1, e2 in clockwise order,
            // assign e1->twin->next = e2 and e2->prev = e1->twin.
            for (auto &x : heMap) {
                Vertex *v = x.first;
                vector<HalfEdge *> vhe = x.second;
                // cout << "At Vertex " << *v << "\n";
                for (unsigned long i = 1; i <= vhe.size(); i++) {
                    HalfEdge *e1 = vhe[i - 1], *e2;
                    if (i == vhe.size()) e2 = vhe[0];
                    else e2 = vhe[i];
                    e1->twin->next = e2;
                    e2->prev = e1->twin;
                }
                if (vhe.size() == 1) { // ex:case where only 2 vertices, one edge exists
                    HalfEdge *e = vhe[0];
                    e->twin->next = e;
                    e->prev = e->twin;
                }
                // assign one of half edges as representative/incident
                // for the vertex
                v->rep = vhe[0];
            }
            // assign face to every cycle of half-edges
            long long faceid = 0;
            for (auto &x : heMap) { // for all vertices
                // Vertex *v = x.first;
                vector<HalfEdge *> vhe = x.second;
                for (HalfEdge *he : vhe) {            // for all their half-edges
                    if (he->face == nullptr) {          // if face is undefined
                        Face *f = new Face(faceid++, he); // create face
                        faces.push_back(f);               // add to list of faces
                        HalfEdge *temp = he->next;
                        while (temp != he) { // for all cyclic half-edges,
                            temp->face = f;    // assign face
                            temp = temp->next;
                        }
                    }
                }
            }
            // DCEL complete
        }
        ~DCEL() { // free allocated memory
            for (auto &x : heMap) {
                Vertex *v = x.first;
                vector<HalfEdge *> y = x.second;
                for (HalfEdge *he : y) {
                    delete he;
                }
                delete v;
            }
        }
};

#endif

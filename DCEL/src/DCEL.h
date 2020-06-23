#ifndef __DCEL_H__
#define __DCEL_H__

#include <map>
#include <set>
#include <vector>
#include <algorithm>

#include "Geometry.h"

using namespace std;

bool compare(const HalfEdge *p, const HalfEdge *q) { // needs revision
    return p->angle > q->angle;
}

class DCEL {
    private:
        unsigned long totalFaces;

        Vertex* inSet(const Vertex &a) {
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
            totalFaces = 0;
            for (auto &x: heMap) { // for all vertices
                // Vertex *v = x.first;
                vector<HalfEdge *> &vhe = x.second;
                for (auto &he: vhe) {            // for all their half-edges
                    if (he->face == nullptr) {          // if face is undefined
                        setFace(he);
                    }
                }
            }
            // DCEL complete
        }

        void setFace(HalfEdge* (&he)) {
            Face *f = new Face(totalFaces++, he); // create face
            faces.push_back(f); // add to list of faces
            he->face = f;
            HalfEdge *temp = he->next;
            while (temp != he) { // for all cyclic half-edges,
                temp->face = f;    // assign face
                temp = temp->next;
            }
        }

        Vertex* getVertex(const Vertex &v) {
            return inSet(v);
        }

        Vertex* addVertex(Vertex *v) {
            Vertex *a = inSet(*v);
            if (a != nullptr) return a;
            heMap[v] = vector<HalfEdge *>{};
            vertices.push_back(v);
            return v;
        }

        Vertex* addVertex(Vertex v) {
            Vertex *a = inSet(v);
            if (a != nullptr) return a;
            a = new Vertex(v);   
            heMap[a] = vector<HalfEdge *>{};
            vertices.push_back(a);
            return a;
        }

        Vertex* addVertex(long x, long y) {
            return addVertex(Vertex(x, y));
        }

        void addEdge(Vertex *a, Vertex *b) {
            a = addVertex(a); // adds if not present
            b = addVertex(b); // adds if not present
            HalfEdge *ab = new HalfEdge(a, b);
            HalfEdge *ba = new HalfEdge(b, a);
            ab->twin = ba;
            ab->next = ba;
            ab->prev = ba;
            ba->twin = ab;
            ba->next = ab;
            ba->prev = ab;
            heMap[a].push_back(ab);
            heMap[b].push_back(ba);
            // TODO: insertion can be done in log(n), right?! (set? list gives o(n))
            sort(heMap[a].begin(), heMap[a].end(), compare);
            sort(heMap[b].begin(), heMap[b].end(), compare);
            for (auto i=heMap[a].begin(); i!=heMap[a].end(); i++) {
                if (*i != ab) continue;
                auto before = (i+1 == heMap[a].end())?heMap[a].begin():i+1;
                HalfEdge *BF = *before;
                HalfEdge *AB = *i;
                AB->twin->next = BF;
                AB->prev = BF->prev;
                AB->prev->next = AB;
                BF->prev = AB->twin;
                break;
            }
            for (auto i=heMap[b].begin(); i!=heMap[b].end(); i++) {
                if (*i != ba) continue;
                auto before = (i+1 == heMap[b].end())?heMap[b].begin():i+1;
                HalfEdge *BF = *before;
                HalfEdge *BA = *i;
                BA->twin->next = BF;
                BA->prev = BF->prev;
                BA->prev->next = BA;
                BF->prev = BA->twin;
                break;
            }
            ab->face = ab->next->next->face;
            ab->face->rep = ab;
            setFace(ba);
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
            for (auto &f: faces) {
                delete f;
            }
        }
};

#endif

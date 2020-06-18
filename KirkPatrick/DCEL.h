#ifndef __DCEL_H__
#define __DCEL_H__

#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class HalfEdge;

class Vertex {
    public:
        long x, y; // coordinates
        HalfEdge *rep; // rep->tail == this
        Vertex() {}
        Vertex(long X, long Y): x(X), y(Y) {}
        Vertex(const Vertex &p): x(p.x), y(p.y) {}
        ~Vertex() {}
};

class Edge {
    public:
        Vertex src, dst;
        Edge() {}
        Edge(Vertex &source, Vertex &destination): 
            src(source), dst(destination) {}
        ~Edge() {}
};

class Face {
    public:
        long long id;
        HalfEdge *rep; // rep->left == this
        Face() {}
        Face(long long Id, HalfEdge *representative): id(Id), rep(representative) {}
        ~Face() {}
};

class HalfEdge {
    public:
        HalfEdge *prev; // prev->next = this
        HalfEdge *next; // next->prev = this
        HalfEdge *twin; // twin->twin = this
        const Vertex *tail; // twin->next->tail == tail && prev->twin->tail == tail
        const Vertex *head; // twin->next->tail == tail && prev->twin->tail == tail
        Face *face; // prev->face == face && next->face == face
        HalfEdge(const Vertex *src, const Vertex *dst): tail(src), head(dst), face(nullptr) {}
        ~HalfEdge() {}
};

bool compare(const HalfEdge *p, const HalfEdge *q) {
    const Vertex *a = p->head, *b = q->head;
    if (a->y*(long long)b->y <= 0) // If a & b have diff signs on their y coordinate?
        return a->y < b->y || (a->y == b->y && a->x < b->x); // Then the one pointing down comes before. If both have y = 0, then test x coord.
    else // Same y signs, establish ordering with a perpdot b.
        return (a->x*(long long)b->y - a->y*(long long)b->x) < 0; 
}

class DCEL {
    public:
      map<Vertex *, vector<HalfEdge *>> heMap;
      vector<Vertex *> vertices;
      vector<Face *> faces;
      DCEL(vector<Edge> &edgelist) {
        // For each edge,
        // Add half edge to the vertex list of its source
        for (Edge &edge : edgelist) {
          Vertex *a = new Vertex(edge.src);
          Vertex *b = new Vertex(edge.dst);
          if (heMap.find(a) == heMap.end()) {
            heMap[a] = vector<HalfEdge *>{};
            vertices.push_back(a);
          }
          if (heMap.find(b) == heMap.end()) {
            heMap[b] = vector<HalfEdge *>{};
            vertices.push_back(a);
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
          for (unsigned long i = 1; i < vhe.size(); i++) {
            HalfEdge *e1 = vhe[i - 1];
            HalfEdge *e2 = vhe[i];
            e1->twin->next = e2;
            e2->prev = e1->twin;
          }
          if (vhe.size() ==
              1) { // ex:case where only 2 vertices, one edge exists
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

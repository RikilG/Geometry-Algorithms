#ifndef __HALFEDGE_H__
#define __HALFEDGE_H__

#include <iostream>
#include <vector>
//forward declarations
class Edge;
class Face;
class Vertex;
class HalfEdge;

using namespace std;

class Vertex {
    public:
        long x, y; // coordinates
        unsigned long tag; // a tag attribute to hold any additional info
        unsigned long parent; // to be used in cycle detection
        HalfEdge *rep; // rep->tail == this
        Vertex(): tag(0) {}
        Vertex(long X, long Y): x(X), y(Y), tag(0) {}
        Vertex(const Vertex &p): x(p.x), y(p.y), tag(p.tag), parent(p.parent) {}
        ~Vertex() {}

        bool operator==(const Vertex &v) {
            return (x == v.x) && (y == v.y);
        }

        bool operator!=(const Vertex &v) {
            return !operator==(v);
        }

        bool operator<(const Vertex &v) const {
            return x < v.x || (x == v.x && y < v.y);
        }

        Vertex operator-(const Vertex &v) {
            return Vertex(x-v.x, y-v.y);
        }
};

ostream& operator<<(ostream &os, const Vertex &v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

class Edge {
    public:
        Vertex src, dst;
        Edge() {}

        Edge(Vertex &source, Vertex &destination): 
            src(source), dst(destination) {}

        Edge(long x1, long y1, long x2, long y2) {
            src = Vertex(x1, y1);
            dst = Vertex(x2, y2);
        }

        ~Edge() {}

        bool operator==(const Edge &e) {
            return src == e.src && dst == e.dst;
        }

        bool operator!=(const Edge &e) {
            return !operator==(e);
        }
};

ostream& operator<<(ostream &os, const Edge &e) {
    os << e.src << " <-> " << e.dst;
    return os;
}

class Face {
    public:
        long long id;
        HalfEdge *rep; // rep->left == this
        Face() {}
        Face(long long Id, HalfEdge *representative): id(Id), rep(representative) {}
        ~Face() {}
};

ostream& operator<<(ostream &os, const Face &f) {
    os << "Face id: " << f.id;// << ", Rep: " << *(f.rep);
    return os;
}

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

ostream& operator<<(ostream &os, const HalfEdge &he) {
    os << "HalfEdge: " << *(he.tail) << " -> " << *(he.head);
    return os;
}

class Triangle {
    public:
        vector<Vertex> v;
        Triangle(vector<Vertex>& vertices) {
            v.push_back(vertices[0]);
            v.push_back(vertices[1]);
            v.push_back(vertices[2]);
        }
        Triangle(Vertex &a, Vertex &b, Vertex &c) {
            v.push_back(a);
            v.push_back(b);
            v.push_back(c);
        }
        ~Triangle() {}
};

ostream& operator<<(ostream &os, const Triangle &t) {
    os << t.v[0] << ", " << t.v[1] << ", " << t.v[2];
    return os;
}

#endif

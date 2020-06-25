/**
 * @file Geometry.h
 * @author Rikil Gajarla (f20170202@hyderabad.bits-pilani.ac.in)
 * @brief This file contains the basic geometric structure such as Vertex, Edge, Face and HalfEdge
 */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <iostream>
#include <cmath>

using namespace std;

const double epsillion = 0.00001;

// forward declarations
class Edge;
class Face;
class Vertex;
class HalfEdge;
ostream& operator<<(ostream &os, const HalfEdge &he);

/**
 * @class Vertex
 * @brief Basic geometric Vertex class to store coordinates of vertex and halfedge
 * 
 * This class stores the (x, y) coordinate of a vertex as taken from the user input. 
 * It also has a HalfEdge object which stores a representative HalfEdge for this vertex
 */
class Vertex {
    public:
        double x, y; // coordinates
        HalfEdge *rep; // rep->tail == this

        /**
         * @brief Construct a new empty Vertex object
         * 
         */
        Vertex() {}

        /**
         * @brief Construct a new Vertex object with the given coordinates
         * 
         * A vertex type object will be constructed with the given coordinates.
         * The pointer to representative HalfEdge will be set to nullptr
         * 
         * @param X x coordinate of the input vertex
         * @param Y y coordinate of the input vertex
         */
        Vertex(double X, double Y): x(X), y(Y), rep(nullptr) {}

        /**
         * @brief Construct a new Vertex object from another Vertex object
         * 
         * This is effectively a copy constructor for the new Vertex object
         * 
         * @param p Vertex type object whose all parameters will be copied
         */
        Vertex(const Vertex &p): x(p.x), y(p.y), rep(p.rep) {}

        /**
         * @brief To overload == operator on Vertex type objects.
         * 
         * This returns true only if both x and y coordinates are equal between
         * the objects being compared. Representative edge is not considered
         * 
         * @param v Vertex object to be compared with
         * @return true if both coordinates match 
         * @return false if at least one coordinate differs
         */
        bool operator==(const Vertex &v) {
            // return (x == v.x) && (y == v.y);
            return (abs(x - v.x) < epsillion) && (abs(y - v.y) < epsillion);
        }

        /**
         * @brief To overload < operator on Vertex type objects.
         * 
         * Vertex a is less than Vertex b (a < b) if x coordinate of a is 
         * lesser than b. In case x coordinate is equal, their y coordinates 
         * are compared.
         * 
         * @param v Vertex object to be compared with
         * @return true if current x coordinate is less than the other (y is used if x is same)
         * @return false otherwise
         */
        bool operator<(const Vertex &v) const {
            return x < v.x || (x == v.x && y < v.y);
        }
};

ostream& operator<<(ostream &os, const Vertex &v) {
    os.precision(10);
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

/**
 * @class Edge
 * @brief Basic geometric Edge class to store endpoints of edges
 * 
 * This class stores the 2 Vertex type objects to represent an edge. Directionality is NOT assumed.
 * For the case of directionality, HalfEdge takes care of it.
 */
class Edge {
    public:
        Vertex src, dst;

        /**
         * @brief Construct a new empty Edge object
         * 
         */
        Edge() {}

        /**
         * @brief Construct a new Edge object from given vertices
         * 
         * To construct a Edge type object from 2 Vertex object. 
         * The parameter names might be misleading, but it is guarenteed that
         * no directionality is assumed
         * 
         * @param source First Vertex object
         * @param destination Second Vertex object
         */
        Edge(Vertex &source, Vertex &destination): 
            src(source), dst(destination) {}

        /**
         * @brief Construct a new Edge object from vertex coordinates
         * 
         * @param x1 x coordinate of first vertex
         * @param y1 y coordinate of first vertex
         * @param x2 x coordinate of second vertex
         * @param y2 y coordinate of second vertex
         */
        Edge(double x1, double y1, double x2, double y2) {
            src = Vertex(x1, y1);
            dst = Vertex(x2, y2);
        }
};

ostream& operator<<(ostream &os, const Edge &e) {
    os << e.src << " <-> " << e.dst;
    return os;
}

/**
 * @class Face
 * @brief Basic geometric Face class to store a Face structure
 * 
 * This Face class has an id and a representative HalfEdge which can be 
 * traversed to get the surrounding vertices and edges.
 * 
 */
class Face {
    public:
        long long id;
        HalfEdge *rep; // rep->left == this

        /**
         * @brief Construct a new empty Face object
         * 
         */
        Face() {}

        /**
         * @brief Construct a new Face object
         * 
         * @param Id id to be given to this face object (must be unique)
         * @param representative A HalfEdge to represent this face (can be any of the incident half edges)
         */
        Face(long long Id, HalfEdge *representative): id(Id), rep(representative) {}
};

ostream& operator<<(ostream &os, const Face &f) {
    os << "Face Id: " << f.id << ", Rep: " << *(f.rep);
    return os;
}

/**
 * @class HalfEdge
 * @brief Basic geometric Face class to store a Face structure
 * 
 * Each Edge will be split into 2 HalfEdges and hence, these are directional. Each HalfEdge
 * object has a next pointer, prev pointer, twin pointer, tail pointer, head pointer and 
 * face pointer to give a complete information about all its incident geometric objects. 
 * This class is the main component of the DCEL structure.
 * 
 */
class HalfEdge {
    public:
        HalfEdge *prev; /**< Pointer to previous HalfEdge such that: prev->next = this */
        HalfEdge *next; /**< Pointer to next HalfEdge such that: next->prev = this */
        HalfEdge *twin; /**< Pointer to the other twin of this edge such that: twin->twin = this */
        const Vertex *tail; /**< Vertex present at tail such that: twin->next->tail == tail && prev->twin->tail == tail */
        const Vertex *head; /**< Vertex present at head */
        Face *face; /**< prev->face == face && next->face == face */
        double angle;

        /**
         * @brief Construct a new Half Edge object
         * 
         * Construct a HalfEdge object from the given 2 vertices. Note that directionality is 
         * important. First argument refers to the src/source/tail whereas the second argument
         * refers to the dst/destination/head.
         * 
         * @param src source or the tail Vertex of the HalfEdge
         * @param dst destination or the head Vertex of the HalfEdge
         */
        HalfEdge(const Vertex *src, const Vertex *dst): tail(src), head(dst), face(nullptr) {
            angle = atan2(dst->y - src->y, dst->x - src->x);
        }
};

ostream& operator<<(ostream &os, const HalfEdge &he) {
    os << "HEdge: " << *(he.tail) << " -> " << *(he.head);
    return os;
}

#endif

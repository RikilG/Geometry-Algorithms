/**
 * @file Geometry.h
 * @author Rikil Gajarla (f20170202@hyderabad.bits-pilani.ac.in)
 * @brief This file contains the implementation of the basic geometric objects such as Vertex, Edge, Face
 * 
 */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <iostream>
#include <vector>
//forward declarations
class Edge;
class Face;
class Vertex;

const float epsillion = 0.001f;

using namespace std;

/**
 * @class Vertex
 * @brief Basic geometric Vertex class to store coordinates of vertex
 * 
 * This class stores the (x, y) coordinate of a vertex as taken from the user input.
 */
class Vertex {
    public:
        float x, y; //< coordinates of the vertex
        unsigned long tag; //< Tag attribute to hold any additional info
        unsigned long parent; //< Denote the index of the parent vertex, To be used in cycle detection

        /**
         * @brief Construct a new empty Vertex object
         * 
         */
        Vertex(): tag(0) {}

        /**
         * @brief Construct a new Vertex object with the given coordinates
         * 
         * A vertex type object will be constructed with the given coordinates.
         * 
         * @param X x coordinate of the input vertex
         * @param Y y coordinate of the input vertex
         */
        Vertex(float X, float Y): x(X), y(Y), tag(0) {}

        /**
         * @brief Construct a new Vertex object with the given coordinates and extra tag
         * 
         * A vertex type object will be constructed with the given coordinates and tag.
         * 
         * @param X x coordinate of the input vertex
         * @param Y y coordinate of the input vertex
         * @param Tag integer tag to be assigned to this vertex
         */
        Vertex(float X, float Y, unsigned long Tag): x(X), y(Y), tag(Tag) {}

        /**
         * @brief Construct a new Vertex object from another Vertex object
         * 
         * This is effectively a copy constructor for the new Vertex object
         * 
         * @param p Vertex type object whose all parameters will be copied
         */
        Vertex(const Vertex &p): x(p.x), y(p.y), tag(p.tag), parent(p.parent) {}
        ~Vertex() {}

        /**
         * @brief To overload == operator on Vertex type objects.
         * 
         * This returns true only if both x and y coordinates are equal between
         * the objects being compared.
         * 
         * @param v Vertex object to be compared with
         * @return true if both coordinates match 
         * @return false if at least one coordinate differs
         */
        bool operator==(const Vertex &v) {
            return (abs(x - v.x) < epsillion) && (abs(y - v.y) < epsillion);
            // return (x == v.x) && (y == v.y);
        }

        /**
         * @brief To overload != operator on Vertex type objects.
         * 
         * This returns NOT of the == overloaded operator
         * 
         * @param v Vertex object to be compared with
         * @return true if at least one coordinate differs
         * @return false if both coordinates match
         */
        bool operator!=(const Vertex &v) {
            return !operator==(v);
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

        /**
         * @brief To overlaod - operator on Vertex type objects
         * 
         * This can be mainly used for applications like shifting the 
         * point with reference to other point. Another application is 
         * subtract operation when the Vertex class is used to represent 
         * vectors(since even vectors attributes are similar to points)
         * 
         * @param v Vertex object to be subtracted
         * @return Vertex Vertex with the final values after subtraction
         */
        Vertex operator-(const Vertex &v) {
            return Vertex(x-v.x, y-v.y);
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
        Edge(float x1, float y1, float x2, float y2) {
            src = Vertex(x1, y1);
            dst = Vertex(x2, y2);
        }

        /**
         * @brief To overload == operator on Edge type objects.
         * 
         * This returns true only if both endpoints match between
         * the objects being compared. The order is considered to be 
         * important as we want to know if its the same edge or not.
         * 
         * @param e Edge object to be compared with
         * @return true if the edge matches 
         * @return false otherwise
         */
        bool operator==(const Edge &e) {
            return src == e.src && dst == e.dst;
        }

        /**
         * @brief To overload != operator on Edge type objects.
         * 
         * This returns NOT of the == overloaded operator
         * 
         * @param e Edge object to be compared with
         * @return true if the edge does not match
         * @return false if the edge matches
         */
        bool operator!=(const Edge &e) {
            return !operator==(e);
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
        Face(long long Id): id(Id) {}
};

ostream& operator<<(ostream &os, const Face &f) {
    os << "Face id: " << f.id;// << ", Rep: " << *(f.rep);
    return os;
}

/**
 * @class Triangle
 * @brief This object is to represent the triangle object with Vertices
 * 
 * This class is just to hold the 3 vertices of the triangle. The purpose 
 * of this class is to provide abstraction in code to convey that we are 
 * dealing with triangles and not just list of vertices
 * 
 */
class Triangle {
    public:
        vector<Vertex> v;

        /**
         * @brief Construct a new Triangle object
         * 
         * @param vertices List of vertices which constitute this triangle
         */
        Triangle(vector<Vertex>& vertices) {
            v.push_back(vertices[0]);
            v.push_back(vertices[1]);
            v.push_back(vertices[2]);
        }

        /**
         * @brief Construct a new Triangle object
         * 
         * @param a First Vertex
         * @param b Second Vertex
         * @param c Third Vertex
         */
        Triangle(Vertex &a, Vertex &b, Vertex &c) {
            v.push_back(a);
            v.push_back(b);
            v.push_back(c);
        }
};

ostream& operator<<(ostream &os, const Triangle &t) {
    os << t.v[0] << ", " << t.v[1] << ", " << t.v[2];
    return os;
}

#endif

#ifndef __EARCLIPPING_H__
#define __EARCLIPPING_H__

#include <cmath>
#include <vector>

#include "Geometry.h"

double det(const Vertex &u, const Vertex &v) {
    return u.x * v.y - u.y * v.x;
}

double dist(Vertex const &u, Vertex const &v) {
    return sqrt(pow((v.x - u.x), 2) + pow((v.y - u.y), 2));
}

bool pointInTriangle(Vertex a, Vertex b, Vertex c, Vertex p) {
    // check if point p is within the triangle abc: the point must be at the left
    // of each edge
    Vertex ab = b - a;
    Vertex bc = c - b;
    Vertex ca = a - c;

    if (det(ab, p - a) > 0 && det(bc, p - b) > 0 && det(ca, p - c) > 0)
        return true;
    else
        return false;
}

vector<Triangle> triangulate(vector<Vertex> points) { // the ear clipping algorithm
    vector<Triangle> triangles;
    vector<Vertex> initialPoints = points;

    if(points.size() < 3) return triangles; // can't have a triangle with < 3 points

    bool cannotTriangulate = false;
    bool triangleFound = true;

    while(points.size() != 0) { // run the algorithm until our polygon is empty
        if(!triangleFound) // one loop didn't find any ear, the program is stuck, the polygon cannot be triangulated (likely to be a 8 shape or self intersecting polygon)
            return triangles ;

        triangleFound = false ; // we want to find a new ear at each loop
        for(int i=0;i<points.size()-2;i++) {
            // for each 3 consecutive points we check if it's an ear : an ear is a triangle that wind in the right direction and that do not contain any other point of the polygon
            if(!triangleFound) {
                bool result = false ;
                if (det(points[i + 1] - points[i], points[i + 2] - points[i + 1]) < 0) {
                    result = true;
                    for (int j = 0; j < initialPoints.size(); j++) {
                        // we check if there's no point inside it
                        if (pointInTriangle(points[i + 2], points[i + 1], points[i], initialPoints[j])) {
                            result = false;
                        }
                    }
                }

                if(result) {
                    triangleFound = true ;
                    triangles.push_back(Triangle(points[i], points[i+1], points[i+2]));
                    // TODO: keep track using list 
                    vector<Vertex> bufferArray;
                    for(int j(0) ; j < points.size() ; j++) {
                        // delete the triangle in the points array
                        if(j != i+1) {
                            // copy all the points in a buffer array except the points we don't want
                            bufferArray.push_back( points[j] );
                        }
                    }
                    points = bufferArray ;
                }
            }
        }
    }
    return triangles ; // we return the triangle array
}


#endif

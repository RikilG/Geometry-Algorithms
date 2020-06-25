/**
 * @file monotoneTriangulation.h
 * @author Rikil Gajarla (f20170202@hyderabad.bits-pilani.ac.in)
 * @brief This file contains the method to triangulate a monotone polygon.
 * 
 */

#ifndef __MONOTONETRIANGULATION_H__
#define __MONOTONETRIANGULATION_H__

#include <list>
#include <vector>
#include <algorithm>
#include "Geometry.h"
#include "Tools.h"

using namespace std;

/**
 * @brief Get the Top Chain of the monotone polygon
 * 
 * @param sorted Vertices of polygon sorted w.r.t x-axis
 * @param original unmodified clockwise ordering of vertices of polygon as given by the user
 * @return vector<Vertex> List of vertices present on the top chain of monotone
 */
vector<Vertex> getTopChain(vector<Vertex>& sorted, vector<Vertex>& original) {
    Vertex left = sorted[0];
    Vertex right = sorted[sorted.size()-1];
    vector<Vertex> chain;
    // in the clockwise ordering of original, find where leftmost vertex is
    unsigned long i = 0;
    for (; i<original.size(); i++) {
        if (original[i] == left) break;
    }
    while(original[i] != right) {
        chain.push_back(original[i]);
        i = (i+1) % original.size();
    }
    chain.push_back(right);
    return chain;
}

/**
 * @brief Get the Bottom Chain of the monotone polygon
 * 
 * @param sorted Vertices of polygon sorted w.r.t x-axis
 * @param original unmodified clockwise ordering of vertices of polygon as given by the user
 * @return vector<Vertex> List of vertices present on the bottom chain of monotone
 */
vector<Vertex> getBottomChain(vector<Vertex>& sorted, vector<Vertex>& original) {
    Vertex left = sorted[0];
    Vertex right = sorted[sorted.size()-1];
    vector<Vertex> chain;
    // in the clockwise ordering of original, find where leftmost vertex is
    unsigned long i = 0;
    for (; i<original.size(); i++) {
        if (original[i] == right) break;
    }
    while(original[i] != left) {
        chain.push_back(original[i]);
        i = (i+1) % original.size();
    }
    chain.push_back(left);
    return vector<Vertex>(chain.rbegin(), chain.rend());
}

/**
 * @brief Assign top or bottom to each vertex and sort them w.r.t x-axis
 * 
 * @param input List of vertices representing the clockwise ordering of polygon vertices
 * @param left The left most Vertex present on the polygon
 * @param right The right most Vertex present on the polygon
 * @return vector<Vertex> x-axis soreted list of Vertices of the polygon
 */
vector<Vertex> preprocess(vector<Vertex> input, Vertex &left, Vertex &right) {
    // in the clockwise ordering of original, find where leftmost vertex is
    unsigned long i = 0;
    for (; i < input.size(); i++) {
        if (input[i] == left)
            break;
    }
    while (input[i] != right) {
        input[i].tag = 0; // topside
        i = (i + 1) % input.size();
    }
    input[i].tag = 0; // both left and right are in topside
    i = (i + 1) % input.size();
    while (input[i] != left) {
        input[i].tag = 1; // bottomside
        i = (i + 1) % input.size();
    }
    // sort wrt x axis
    sort(input.begin(), input.end());
    return input;
}

/**
 * @brief Check if the triangle formed by the vertices is valid
 * 
 * A triangle is said to be valid only if it completely exists inside the 
 * polygon
 * 
 * @param a First Vertex
 * @param b Second Vertex
 * @param c Third Vertex
 * @param midSide Side of the middle vertex (top or bottom as set in the tag of Vertex)
 * @return true If the triangle formed is valid
 * @return false otherwise
 */
bool validTriangle(Vertex &a, Vertex &b, Vertex &c, bool midSide) {
    Vertex ab = b-a;
    Vertex bc = c-b;
    if (midSide) { // bottomside
        return det(ab, bc) > 0;
    }
    else { // topside
        return det(ab, bc) < 0;
    }
}

/**
 * @brief Get the minimum Vertex (based on the x-axis)
 * 
 * @param input List of vertices of polygon
 * @return Vertex The minimum vertex
 */
Vertex findMin(const vector<Vertex> &input) {
    Vertex mn = input[0];
    for (const Vertex &v: input) mn = min(mn, v);
    return mn;
}

/**
 * @brief Get the maximum Vertex (based on the x-axis)
 * 
 * @param input List of vertices of polygon
 * @return Vertex The maximum vertex
 */
Vertex findMax(const vector<Vertex> &input) {
    Vertex mx = input[0];
    for (const Vertex &v: input) mx = max(mx, v);
    return mx;
}

/**
 * @brief This method performs the triangulation of the given monotone
 * 
 * @param input List of vertices present on the monotone in clockwise order
 * @return vector<Triangle> List of Triangle objects produced after triangulating the monotone
 */
vector<Triangle> monotoneTriangulate(vector<Vertex> input) {
    vector<Triangle> output;
    Vertex left = findMin(input), right = findMax(input);
    // assign chain sides and sort input w.r.t x axis
    input = preprocess(input, left, right);
    list<Vertex> stk; // queue/stack chain (also the reflex chain)
    unsigned long i=0;
    while(i != input.size()) {
        if (stk.size() < 2) {
            stk.push_back(input[i]);
            i++;
            continue;
        }
        Vertex p, u; // p = vertex eliminated if triangulated, u = adjoining to p
        Vertex v = input[i]; // new vertex
        bool vSide = v.tag;
        if (vSide == stk.back().tag) { // same side
            while (stk.size() >= 2) {
                p = stk.back();
                stk.pop_back();
                u = stk.back();
                if (validTriangle(u, p, v, p.tag)) {
                    output.emplace_back(u, p, v);
                } else {
                    stk.push_back(p); // push the popped vertex to chain
                    break;            // since we can't form proper triangles
                }
            }
        } else { // opposite side, just add diagonals to triangulate
            while (stk.size() >= 2) {
                p = stk.front();
                stk.pop_front();
                u = stk.front();
                output.emplace_back(v, p, u);
            }
        }
        stk.push_back(v); // add current vertex to stack
        i++;
    }
    return output;
}

#endif

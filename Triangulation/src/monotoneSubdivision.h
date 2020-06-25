/**
 * @file monotoneSubdivision.h
 * @author Rikil Gajarla (f20170202@hyderabad.bits-pilani.ac.in)
 * @brief This file contains the algorithm to subdivide the polygon into monotones.
 * 
 */

#ifndef __MONOTONESUBDIVISION_H__
#define __MONOTONESUBDIVISION_H__

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include "Geometry.h"
#include "Tools.h"

using namespace std;

/**
 * @class Graph
 * @brief This class stores the graph representation of the input polygon
 * 
 */
class Graph {
    private:
        map<unsigned long, vector<unsigned long>> adjList; //< adjacency list to store the connections of each vertex
        unsigned long originalSize; //< number of nodes present in the graph
        vector<pair<Vertex, Vertex>> additions; //< List of diagonals which are added to triangulate

    public:
        vector<Vertex> original; //< The original list of untouched polygon vertices as given in clockwise order

        /**
         * @brief Construct a new Graph object from the clockwise ordering of vertices
         * 
         * @param input input vertices of polygon as given in clockwise order
         */
        Graph(vector<Vertex> &input) { // clockwise ordering of vertices
            originalSize = input.size();
            original = input;
            for (unsigned long i=0;i<original.size();i++) { // i has edge with j(i+1)
                unsigned long j = (i+1)%originalSize;
                adjList[i].push_back(j);
                adjList[j].push_back(i);
                original[i].tag = i; // save vertex index to its tag.
            }
        }

        /**
         * @brief connect or draw diagonal to the given Vertices 
         * 
         * @param u First Vertex
         * @param v Second Vertex
         */
        void connect(const Vertex &u, const Vertex &v) {
            // TODO: think about perf analysis by using a set for finding
            unsigned long a = u.tag, b = v.tag;
            if (find(adjList[a].begin(), adjList[a].end(), b) == adjList[a].end())
                adjList[a].push_back(b);
            if (find(adjList[b].begin(), adjList[b].end(), a) == adjList[b].end())
                adjList[b].push_back(a);
            if (u.tag - v.tag < 1 || u.tag - v.tag > 1) { // vertices not next to each other
                additions.push_back(make_pair(u, v));
            }
        }

        /**
         * @brief The previous vertex to the given vertex in the clockwise ordering
         * 
         * @param v Vertex to which we need previous vertex
         * @return Vertex The previous Vertex to the given vertex
         */
        Vertex prev(Vertex &v) {
            for (unsigned long i = 0; i<original.size(); i++) {
                if (original[i] == v) {
                    if (i > 0) return original[i-1];
                    else return original[originalSize-1];
                }
            }
            return Vertex(0, 0);
        }

        /**
         * @brief The next vertex to the given vertex in the clockwise ordering
         * 
         * @param v Vertex to which we need next vertex
         * @return Vertex The next Vertex to the given vertex
         */
        Vertex next(Vertex &v) {
            for (unsigned long i = 0; i<original.size(); i++) {
                if (original[i] == v) {
                    if (i < originalSize - 1) return original[i + 1];
                    else return original[0];
                }
            }
            return Vertex(0, 0);
        }

        /**
         * @brief Get the Sub Polygons of the Graph object
         * 
         * This function returns all the sub polygons which resulted after drawing 
         * diagonals excluding the original polygon itself. In case no diagonals 
         * have been drawn, it returns an empty list.
         * 
         * @return list<vector<Vertex>> List of sub polygons (cloclwise ordering of points in each polygon)
         */
        list<vector<Vertex>> getSubPolygons() {
            // cycle detection algo to find monotones/polygons and return
            // them except the full polygon itself (use originalSize to compare)
            list<vector<Vertex>> monotones;
            monotones.push_back(original);
            for (auto &p: additions) {
                Vertex &u = p.first;
                Vertex &v = p.second;
                for (auto itr = monotones.begin(); itr != monotones.end(); itr++) {
                    auto m = *itr;
                    auto start = find(m.begin(), m.end(), u);
                    auto end = find(m.begin(), m.end(), v);
                    if (start != m.end() && end != m.end()) { // if both vertices exist in one chain
                        vector<Vertex> left;
                        vector<Vertex> right;
                        auto i=start;
                        for (;i!=end;i++) {
                            if (i == m.end()) i = m.begin();
                            if (i == end) break;
                            left.push_back(*i);
                        }
                        left.push_back(*end);
                        for (;i!=start;i++) {
                            if (i == m.end()) i = m.begin();
                            if (i == start) break;
                            right.push_back(*i);
                        }
                        right.push_back(*start);
                        monotones.erase(itr);
                        monotones.push_back(left);
                        monotones.push_back(right);
                        break;
                    }
                }
            }
            return monotones;
        }
};

/**
 * @class SweepStatus
 * @brief This class represents the sweep line status for the plane sweep algorithm
 * 
 * This class stores the edges which are intersecting with the plane at the current 
 * position. the Edges are ordered based on increasing y coordinate. Provides methods
 * to insert, delete and fetch the intersecting edges
 * 
 */
class SweepStatus {
    private:
        list<pair<Edge, Vertex>> edges; //< The list of Edges which are currently intersecting with the sweep line/plane

    public:

        /**
         * @brief Construct a new Sweep Line Status object
         * 
         */
        SweepStatus() {}

        /**
         * @brief get the helper Vertex of the given Edge
         * 
         * @param e Edge to which we need the helper for
         * @return Vertex The helper vertex of the given edge: helper(e)
         */
        Vertex helper(Edge &e) {
            // get the helper vertex of this edge
            for (auto itr = edges.begin(); itr != edges.end(); itr++) {
                auto p = *itr;
                if (p.first == e) return p.second;
            }
            return Vertex(0, 0);
        }

        /**
         * @brief Set the helper Vertex for given Edge
         * 
         * setHelper sets helper(e) = v.
         * 
         * @param e Edge for which helper must be assigned
         * @param v Vertex to be assigned as helper
         */
        void setHelper(Edge e, Vertex v) {
            for (auto &p: edges) {
                if (p.first == e) {
                    p.second = v;
                    break;
                }
            }
        }

        /**
         * @brief Insert a new Edge and its helper into the Sweep Line Status
         * 
         * @param e Edge to insert into status
         * @param helper helper Vertex of given Edge.
         */
        void insert(const Edge &e, const Vertex &helper) {
            for (auto itr = edges.begin(); itr != edges.end(); itr++) {
                auto p = *itr;
                Edge &test = p.first;
                Vertex t = (test.src.y>test.dst.y)?test.src:test.dst;
                Vertex u = (e.src.y>e.dst.y)?e.dst:e.src;
                if (u.y < t.y) { // insert in this pos
                    edges.insert(itr, make_pair(e, helper));
                    return;
                }
            }
            edges.push_back(make_pair(e, helper));
        }

        /**
         * @brief Get the Edge which is immediately above the given Vertex in the polygon
         * 
         * @param v Vertex whose upper Edge is required
         * @return Edge The edge immediately above Vertex v
         */
        Edge getUpper(const Vertex &v) {
            for (auto itr = edges.rbegin(); itr != edges.rend(); itr++) {
                Edge e = (*itr).first;
                if (e.src == v || e.dst == v) {
                    return (*itr).first;
                }
                if (orient(e.src, e.dst, v) >= 0) {
                    return (*(--itr)).first;
                }
            }
            return (*edges.begin()).first;
        }

        /**
         * @brief Remove the given Edge from the Sweep Line Status
         * 
         * This operation can be done preferably when the sweep line/plane is no 
         * longer intersecting with the Edge.
         * 
         * @param e Edge to be removed from the status
         */
        void remove(const Edge &e) {
            for (auto itr = edges.begin(); itr != edges.end(); itr++) {
                if ((*itr).first == e) {
                    edges.erase(itr);
                    return;
                }
            }
        }
};

/**
 * @brief try to fix and connect the Vertex v to the helper of Edge e 
 * 
 * This method only connects v to helper(e) only if v is a merge vertex
 * 
 * @param v Vertex who needs to be connected to a helper
 * @param e The upper Edge whose helper us used to draw diagonal
 * @param graph The current Graph object on which the operations are performed
 * @param status The current SweepStatus object which contains all the intersecting edges
 */
void fixup(Vertex &v, Edge &e, Graph &graph, SweepStatus &status) {
    Vertex helper = status.helper(e);
    // if helper is a merge vertex, add diagonal from v to this vertex
    Vertex hPrev = graph.prev(helper); // previous vertex of helper
    Vertex hNext = graph.next(helper); // next vertex of helper
    if (hPrev.x < helper.x && hNext.x < helper.x && orient(hPrev, helper, hNext) > 0) { // if merge vertex
        graph.connect(helper, v);
    }
}

void checkSort(vector<Vertex>& events, vector<Vertex>& original) {
    for (unsigned long i=0; i<events.size()-1; i++) {
        if (events[i].x == events[i+1].x) {
            if (original[(events[i].tag+1)%original.size()] == events[i+1]) {
                auto &test = original[(events[i].tag+2)%original.size()];
                // if test.x > events[i].x, we are on upside of polygon and no changes required
                // if test.x < events[i].x, we are on lower side, swap.
                if (test.x < events[i].x) {
                    swap(events[i], events[i+1]);
                }
            }
            else if (original[(events[i].tag-1)%original.size()] == events[i+1]) {
                auto &test = original[(events[i].tag+1)%original.size()];
                if (test.x > events[i].x) {
                    swap(events[i], events[i+1]);
                }
            }
        }
    }
}

/**
 * @brief Returns the monotones present in the input polygon
 * 
 * This is the main function which performs plane sweep algorithm to 
 * detect and return the monotones present in the polygon after adding
 * required diagonals
 * 
 * @param input Clockwise ordering of vertices of input polygon
 * @return list<vector<Vertex>> List of polygons which are monotone (vertices of each monotone are clockwise ordered)
 */
list<vector<Vertex>> getMonotones(vector<Vertex> input) {
    vector<vector<Vertex>> monotones;
    Graph graph(input);
    SweepStatus status;
    vector<Vertex> events = graph.original;
    // events are vertices of polygon stored in sorted order (by x-axis)
    sort(events.begin(), events.end());
    // check sort at same x coordinate points
    checkSort(events, graph.original);
    for (Vertex &v: events) { // for each event
        Vertex u = graph.prev(v);
        Vertex w = graph.next(v);
        // orient < 0: inner angle and orient > 0: reflex angle
        // 6 possible cases for each event
        // cout << "Processing: " << u << " " << v << " " << w << "\n";
        if (v.x < u.x && v.x < w.x && orient(u, v, w) < 0) { // Start Vertex
            // both edges lie to the right of v, int.angle smaller than pi
            status.insert(Edge(v, w), v);
            // cout << "StV: " << v << "\n";
            // cout << "ins: " << Edge(v, w) << "\n";
        }
        else if (u.x < v.x && w.x < v.x && orient(u, v, w) < 0) { // End Vertex
            // both edges lie to the left of v, int.angle smaller than pi
            Edge e = status.getUpper(v);
            fixup(v, e, graph, status);
            status.remove(Edge(u, v));
        }
        else if (v.x < u.x && v.x < w.x && orient(u, v, w) > 0) { // Split Vertex: looks like start vertex but angle is reflex
            Edge e = status.getUpper(v);
            graph.connect(v, status.helper(e));
            status.insert(Edge(v, w), v);
            // cout << "SplitV: " << v << "\n";
            // cout << "conn: " << v << ", " << status.helper(e) << "\n";
            // cout << "ins: " << Edge(v, w) << "\n";
        }
        else if (u.x < v.x && w.x < v.x && orient(u, v, w) > 0) { // Merge Vertex: looks like end vertex but angle is reflex
            Edge eb = Edge(u, v);
            status.remove(eb);
            Edge e = status.getUpper(v);
            fixup(v, e, graph, status);
            fixup(v, eb, graph, status);
            status.setHelper(e, v);
            // cout << "MergeV: " << v << "\n";
            // cout << "rm: " << Edge(u,v) << "\n";
        }
        else if (u.x <= v.x && v.x <= w.x) { // Upper Chain Vertex, same x coordinate degenarate case included
            // one vertex to right and one to left with polygon interior below
            Edge e = Edge(u, v);
            fixup(v, e, graph, status);
            // cout << "UC-fixup: " << e << ", h: " << status.helper(e) << ", " << v << "\n";
            status.remove(e);
            status.insert(Edge(v, w), v);
            // cout << "rm: " << e << "\n";
            // cout << "ins: " << Edge(v,w) << "\n";
        }
        else if (w.x <= v.x && v.x <= u.x) { // Lower Chain Vertex
            // one vertex to right and one to left with polygon interior above
            Edge e = status.getUpper(v);
            fixup(v, e, graph, status);
            // cout << "LC-fixup: " << e << ", h: " << status.helper(e) << ", " << v << "\n";
        }
        else { // when orient == 0 and u-v-w are collinear points parallel to y-axis
            // this is a degenarate case.
            // cout << "!!!!!DC!!!!!!\n";
            if (w.y > v.y) { // part of upper edge
                status.remove(Edge(u, v));
                status.insert(Edge(v, w), v);
            }
            else { // part of lower edge
                status.remove(Edge(v, w));
                status.insert(Edge(u, v), v);
            }
        }
    }
    return graph.getSubPolygons();
}

#endif

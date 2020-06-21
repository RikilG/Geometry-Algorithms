#ifndef __MONOTONESUBDIVISION_H__
#define __MONOTONESUBDIVISION_H__

#include <list>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include "Geometry.h"
#include "Tools.h"

using namespace std;

class Graph {
    private:
        map<unsigned long, vector<unsigned long>> adjList;
        unsigned long originalSize;
        vector<pair<Vertex, Vertex>> additions;
    public:
        vector<Vertex> original;

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

        ~Graph() {}

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

        Vertex prev(Vertex &v) {
            for (unsigned long i = 0; i<original.size(); i++) {
                if (original[i] == v) {
                    if (i > 0) return original[i-1];
                    else return original[originalSize-1];
                }
            }
            return Vertex(0, 0);
        }

        Vertex next(Vertex &v) {
            for (unsigned long i = 0; i<original.size(); i++) {
                if (original[i] == v) {
                    if (i < originalSize - 1) return original[i + 1];
                    else return original[0];
                }
            }
            return Vertex(0, 0);
        }

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

class SweepStatus {
    // store edges which intersect sweepline, sorted from top to bottom
    // efficiency: need insert, delete, find, predecessor, successor in log n
    // TODO: currently using O(n), need log n
    private:
        list<pair<Edge, Vertex>> edges;
    public:
        SweepStatus() {}

        Vertex helper(Edge &e) {
            // get the helper vertex of this edge
            for (auto itr = edges.begin(); itr != edges.end(); itr++) {
                auto p = *itr;
                if (p.first == e) return p.second;
            }
            return Vertex(0, 0);
        }

        void setHelper(Edge e, Vertex v) {
            for (auto &p: edges) {
                if (p.first == e) {
                    p.second = v;
                    break;
                }
            }
        }

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

        void remove(const Edge &e) {
            for (auto itr = edges.begin(); itr != edges.end(); itr++) {
                if ((*itr).first == e) {
                    edges.erase(itr);
                    return;
                }
            }
        }
};

void fixup(Vertex &v, Edge &e, Graph &graph, SweepStatus &status) {
    Vertex helper = status.helper(e);
    // if helper is a merge vertex, add diagonal from v to this vertex
    Vertex hPrev = graph.prev(helper); // previous vertex of helper
    Vertex hNext = graph.next(helper); // next vertex of helper
    if (hPrev.x < helper.x && hNext.x < helper.x && orient(hPrev, helper, hNext) > 0) { // if merge vertex
        graph.connect(helper, v);
    }
}

list<vector<Vertex>> getMonotones(vector<Vertex> input) {
    vector<vector<Vertex>> monotones;
    Graph graph(input);
    SweepStatus status;
    vector<Vertex> events = graph.original;
    // events are vertices of polygon stored in sorted order (by x-axis)
    sort(events.begin(), events.end());
    for (Vertex &v: events) { // for each event
        Vertex u = graph.prev(v);
        Vertex w = graph.next(v);
        // orient < 0: inner angle and orient > 0: reflex angle
        // 6 possible cases for each event
        if (v.x < u.x && v.x < w.x && orient(u, v, w) < 0) { // Start Vertex
            // both edges lie to the right of v, int.angle smaller than pi
            status.insert(Edge(v, w), v);
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
        }
        else if (u.x < v.x && w.x < v.x && orient(u, v, w) > 0) { // Merge Vertex: looks like end vertex but angle is reflex
            Edge eb = Edge(u, v);
            status.remove(eb);
            Edge e = status.getUpper(v);
            fixup(v, e, graph, status);
            fixup(v, eb, graph, status);
            status.setHelper(e, v);
        }
        else if (u.x < v.x && v.x < w.x) { // Upper Chain Vertex
            // one vertex to right and one to left with polygon interior below
            Edge e = Edge(u, v);
            fixup(v, e, graph, status);
            status.remove(e);
            status.insert(Edge(v, w), v);
        }
        else if (w.x < v.x && v.x < u.x) { // Lower Chain Vertex
            // one vertex to right and one to left with polygon interior above
            Edge e = status.getUpper(v);
            fixup(v, e, graph, status);
        }
        else { // when orient == 0 and u-v-w are collinear points parallel to y-axis
            // this is a degenarate case.
            // TODO
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

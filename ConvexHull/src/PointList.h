#ifndef __POINTLIST_H__
#define __POINTLIST_H__

#include <vector>
#include <iterator>
#include "Point.h"

using namespace std;

class PointList {
private:
    vector<Point> pts;
    bool sentinels;
    Point lsentinal, rsentinal;

public:
    PointList(): sentinels(false) {}
    PointList(vector<Point> points): pts(points), sentinels(false) {}
    ~PointList() {}

    void setSentinels(bool value, bool upperHull) {
        sentinels = value;
        if (value) {
            Point last = pts[pts.size()-1];
            lsentinal = Point(pts[0].x-1, (upperHull)?pts[0].y-1:pts[0].y+1); // LONG_MIN
            rsentinal = Point(last.x+1, (upperHull)?last.y-1:last.y+1); // LONG_MAX
        }
    }

    auto emplace_back(long a, long b) {
        return pts.emplace_back(a, b);
    }

    auto push_back(Point& p) {
        return pts.push_back(p);
    }

    auto size() {
        return pts.size();
    }

    auto begin() {
        return pts.begin();
    }

    auto end() {
        return pts.end();
    }

    auto erase(size_t idx1, size_t idx2) {
        return pts.erase(pts.begin()+idx1, pts.begin()+idx2+1);
    }

    void print() {
        for (const Point &p: pts) cout << p << " ";
        cout << "\n";
    }

    void print(int s, int e) {
        for (int i=s;i<=e;i++) cout << pts[i] << " ";
        cout << "\n";
    }

    Point& operator[](long long idx) {
        if (!sentinels) return pts[idx];
        if (idx < 0) {
            return lsentinal;
        }
        else if (idx >= pts.size()) {
            return rsentinal;
        }
        else return pts[idx];
    }
};

#endif
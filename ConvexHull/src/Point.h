#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include <vector>

// output string formatting colors, if terminal supports
std::string red = "\033[31;1m", green = "\033[32;1m", reset = "\033[0m";

class Point {
public:
    long x, y;
    Point() {}
    Point(long X, long Y): x(X), y(Y) {}
    ~Point() {}
    bool operator==(const Point &p) {
        return (x==p.x && y == p.y);
    }
};

std::ostream& operator<<(std::ostream &os, const Point &p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

#endif
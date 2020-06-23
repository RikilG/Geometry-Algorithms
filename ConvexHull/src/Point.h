/**
 * \file Point.h
 * \brief This file contains the implementation of the Point class
 * 
 */

#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include <vector>

// output string formatting colors, if terminal supports
std::string red = "\033[31;1m", green = "\033[32;1m", reset = "\033[0m";

/**
 * \class Point
 * \brief Structure to efficiently store and compare points
 */
class Point {
    public:
        long x; /**< x coordinate of the point */
        long y; /**< y coordinate of the point */
        
        /**
         * \brief Default constructor for Point class
         */
        Point() {}

        /**
         * \brief Constructor for Point class
         * \param X x coordinate of point
         * \param Y y coordinate of point
         */
        Point(long X, long Y): x(X), y(Y) {}
        
        bool operator==(const Point &p) {
            return (x==p.x && y == p.y);
        }
};

std::ostream& operator<<(std::ostream &os, const Point &p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

#endif
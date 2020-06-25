/**
 * \file PointList.h
 * \brief This file contains the implementation of PointList class
 * 
 * PointList class, although similar to c++ vector tries to extend the default
 * vector capabilities. The main reason for this class to exist is due to the 
 * requirement of sentinel nodes while computing the upper and lower tangents.
 */

#ifndef __POINTLIST_H__
#define __POINTLIST_H__

#include <vector>
#include <iterator>
#include "Point.h"

using namespace std;

/**
 * \class PointList
 * \brief Structure to store a list of Point class objects(points)
 * 
 * This class gives functionality to store a list of Point objects with additional
 * support of having sentinel nodes which are auto determined by the class based on
 * points present in its list.
 */
class PointList {
    private:
        vector<Point> pts; /**< STL vector object to store points */
        bool sentinels; /**< boolean to denote if sentinels are present or absent */
        Point lsentinal; /**< Left sentinal point coordinates, auto-determined */
        Point rsentinal; /**< Right sentinal point coordinates, auto-determined */

    public:
        /**
         * \brief Default constructor for Point class
         */
        PointList(): sentinels(false) {}

        /**
         * \brief vector based constructor for Point class
         * \param points vector of Point objects used to initialize PointList
         */
        PointList(vector<Point> points): pts(points), sentinels(false) {}

        /**
         * \brief add or remove sentinel nodes
         * \param value boolean value which when set to true, sets the sentinel nodes for this PointList
         * \param upperHull boolean value to be set to true if the current operations are to be performed on upper hull
         */
        void setSentinels(bool value, bool upperHull) {
            sentinels = value;
            if (value) {
                Point last = pts[pts.size()-1];
                lsentinal = Point(pts[0].x-1, (upperHull)?pts[0].y-1:pts[0].y+1); // LONG_MIN
                rsentinal = Point(last.x+1, (upperHull)?last.y-1:last.y+1); // LONG_MAX
            }
        }

        /// To provide interface to STL vector's emplace_back() function
        auto emplace_back(double a, double b) {
            return pts.emplace_back(a, b);
        }

        /// To provide interface to STL vector's push_back() function
        auto push_back(Point& p) {
            return pts.push_back(p);
        }

        /// To provide interface to STL vector's size() function
        auto size() {
            return pts.size();
        }

        /// To provide interface to STL vector's begin() function which returns iterator to the start of container
        auto begin() {
            return pts.begin();
        }

        /// To provide interface to STL vector's end() function which returns iterator to the end of container
        auto end() {
            return pts.end();
        }

        /**
         * \brief erase the points present in the given range of indices
         * \param idx1 index from which points must be erased
         * \param idx2 index until which all points will be erased (inclusive)
         */
        auto erase(size_t idx1, size_t idx2) {
            return pts.erase(pts.begin()+idx1, pts.begin()+idx2+1);
        }

        /**
         * \brief print the points contained in this PointList object
         */
        void print() {
            for (const Point &p: pts) cout << p << " ";
            cout << "\n";
        }

        /**
         * \brief print the points contained in this PointList in the specified range
         * \param s starting index to start printing from
         * \param e ending index to end printing at (inclusive)
         */
        void print(int s, int e) {
            for (int i=s;i<=e;i++) cout << pts[i] << " ";
            cout << "\n";
        }

        /**
         * \brief To provide interface to STL vector's access operator []. Also considers sentinel nodes if index is <0 or >=size of PointList
         * \param idx index which is to be accessed.
         */
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
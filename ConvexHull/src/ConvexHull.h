/**
 * \file ConvexHull.h
 * \brief This file contains the main Convex Hull algorithm
 * 
 * This header file (ConvexHull.h) file consists of main convexHull() function
 * along with it's helper functions for calculating upper and lower tangents. 
 * This file also depends on these headers: Point.h, Tools.h and PointList.h
 */

#ifndef __CONVEXHULL_H__
#define __CONVEXHULL_H__

#include <vector>
#include <algorithm>

#include "Point.h"
#include "Tools.h"
#include "PointList.h"

using namespace std;

/**
 * \brief comparator function used to compare x coordinates while sorting
 * \param a first Point object
 * \param b second Point object
 * \return true if a comes before b
 */
bool xPointComparator(const Point &a, const Point &b) {
    return (a.x < b.x);
}

/**
 * \brief function to sort given list of points in increasing order of x coordinate
 * \param input PointList object containing the user input data points
 */
void xAxisSort(PointList &input) {
    sort(input.begin(), input.end(), xPointComparator);
}

/**
 * \brief compute the upper tangent for the given left hull and right hull
 * \param lHull PointList object contaning the points on the left hull in clockwise order
 * \param rHull PointList object containig the points on the right hull in clockwise order
 * \return a STL pair object with the points which are part of upper tangent between both hulls
 */
pair<long long, long long> upperTangent(PointList& lHull, PointList& rHull) {
    lHull.setSentinels(true, true);
    rHull.setSentinels(true, true);
    // temp indices to points, to walk on hull, initialized to sentinals(extremes)
    long long lp = lHull.size()-1, lq = lHull.size()-2, rp = 0, rq = 1;
    bool check; // condition to break loop in case of colinear points
    while (!( orient(lHull[lp], rHull[rp], rHull[rq])<0 && orient(rHull[rp], lHull[lp], lHull[lq])>0 )) {
        check = false;
        while (orient(lHull[lp], rHull[rp], rHull[rq]) >= 0) {
            if (rq >= rHull.size()) break;
            check = true;
            rp++;
            rq++;
        }
        while (orient(rHull[rp], lHull[lp], lHull[lq]) <= 0) {
            if (lq <= -1) break;
            check = true;
            lp--;
            lq--;
        }
        if (rq == rHull.size() && lq == -1) break;
        else if (check == false) break;
    }
    return make_pair(lp, rp);
}

/**
 * \brief compute the lower tangent for the given left hull and right hull
 * \param lHull PointList object contaning the points on the left hull in clockwise order
 * \param rHull PointList object containig the points on the right hull in clockwise order
 * \return a STL pair object with the points which are part of lower tangent between both hulls
 */
pair<long long, long long> lowerTangent(PointList& lHull, PointList& rHull) {
    lHull.setSentinels(true, false);
    rHull.setSentinels(true, false);
    // temp indices to points, to walk on hull, initialized to sentinals(extremes)
    long long lp = lHull.size()-1, lq = lHull.size()-2, rp = 0, rq = 1;
    bool check;
    while (!( orient(lHull[lp], rHull[rp], rHull[rq])>0 && orient(rHull[rp], lHull[lp], lHull[lq])<0 )) {
        check = false;
        while (orient(lHull[lp], rHull[rp], rHull[rq]) <= 0) {
            if (rq >= rHull.size()) break;
            check = true;
            rp++;
            rq++;
        }
        while (orient(rHull[rp], lHull[lp], lHull[lq]) >= 0) {
            if (lq <= -1) break;
            check = true;
            lp--;
            lq--;
        }
        if (rq == rHull.size() && lq == -1) break;
        else if (check == false) break;
    }
    return make_pair(lp, rp);
}

/**
 * \brief Function to combine the upper hull and the lower hull
 * \param uHull PointList object with points of upper hull in clockwise order
 * \param lHull PointList object with points of lower hull in clockwise order
 * \return PointList object with the final list of points present on the complete convex hull in clockwise order
 */
PointList combineHulls(PointList &uHull, PointList &lHull) {
    PointList output;
    for (long long i=uHull.size()-1;i>=0;i--) output.push_back(uHull[i]); //ccw direction
    for (long long i=0;i<lHull.size();i++) {
        if (i == 0 && output[output.size()-1] == lHull[0]) continue;
        else if (i == lHull.size()-1 && lHull[i] == output[0]) continue;
        else output.push_back(lHull[i]);
    }
    return output;
}

/**
 * \brief Recursive function to compute the upper hull of the left half and right half points then merge them with upper tangent
 * \param input input points which are sorted w.r.t x coordinate
 * \param start start index of interval over which upper hull is computed
 * \param end ending index of interval over which upper hull is computed
 * \return PointList with all Points present on upper hull of given interval (in clockwise order)
 */
PointList upperConvexHull(PointList &input, int start, int end) {
    PointList output;
    if (end-start+1 <= 3) { // base case
        if (end-start+1 == 3 && orient(input[start], input[start+1], input[end])>0) {// problematic
            output.push_back(input[start]);
            output.push_back(input[end]);
        }
        else {
            for (long long i=start;i<=end;i++) output.push_back(input[i]);
        }
        return output;
    }
    long long mid = (start + end)/2;
    PointList lHull = upperConvexHull(input, start, mid); // left hull
    PointList rHull = upperConvexHull(input, mid+1, end); // right hull
    pair<long long, long long> ut = upperTangent(lHull, rHull);
    for (long long i=0;i<=ut.first;i++) output.push_back(lHull[i]);
    for (long long i=ut.second;i<rHull.size();i++) output.push_back(rHull[i]);
    return output;
}

/**
 * \brief Recursive function to compute the lower hull of the left half and right half points then merge them with lower tangent
 * \param input input points which are sorted w.r.t x coordinate
 * \param start start index of interval over which lower hull is computed
 * \param end ending index of interval over which lower hull is computed
 * \return PointList with all Points present on lower hull of given interval (in clockwise order)
 */
PointList lowerConvexHull(PointList &input, int start, int end) {
    PointList output;
    if (end-start+1 <= 3) { // base case
        if (end-start+1 == 3 && orient(input[start], input[start+1], input[end])<0) {// problematic
            output.push_back(input[start]);
            output.push_back(input[end]);
        }
        else {
            for (long long i=start;i<=end;i++) output.push_back(input[i]);
        }
        return output;
    }
    long long mid = start + ((end - start)/2); // = (start + end)/2
    PointList lHull = lowerConvexHull(input, start, mid); // left hull
    PointList rHull = lowerConvexHull(input, mid+1, end); // right hull
    pair<long long, long long> lt = lowerTangent(lHull, rHull);
    for (long long i=0;i<=lt.first;i++) output.push_back(lHull[i]);
    for (long long i=lt.second;i<rHull.size();i++) output.push_back(rHull[i]);
    return output;
}

/**
 * \brief driver function which computes upper hull, lower hull and then combines them
 * \param input input points given by user over which convex hull is computed
 * \return Points present on the convex hull of given points in clockwise order 
 */
PointList convexHull(PointList &input) {
    xAxisSort(input);
    PointList uHull = upperConvexHull(input, 0, input.size()-1);
    PointList lHull = lowerConvexHull(input, 0, input.size()-1);
    PointList output = combineHulls(uHull, lHull);
    return output;
}

#endif
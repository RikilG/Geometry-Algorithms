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

bool xPointComparator(const Point &a, const Point &b) {
    return (a.x < b.x);
}

void xAxisSort(PointList &input) {
    sort(input.begin(), input.end(), xPointComparator);
}

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

PointList convexHull(PointList &input) {
    xAxisSort(input);
    PointList uHull = upperConvexHull(input, 0, input.size()-1);
    PointList lHull = lowerConvexHull(input, 0, input.size()-1);
    PointList output = combineHulls(uHull, lHull);
    return output;
}

#endif
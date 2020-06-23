# Convex Hull

## Introduction

Given a set of points P, the Convex Hull of P, denoted conv(P) is the smallest closed
simple polygon which contains all the points in P. It can be visualized as a tightly
snapped rubber band over the given set of points.

We would like to compute the convex hull of given set of points by using a divide and
conquer technique. Later, we will also show that the computational complexity of our 
algorithm is also O(n log n). Note that we cannot do better than is for computing 
convex hull

## How to Run

The src folder contains the source code for the convex hull program. `g++` from the GNU
compiler suite is required to compile the program to a executable.

Steps to Compile:

1) `cd` into the src directory
2) Run `g++ main.cpp` which generates an executable called `a.out` in the same directory
3) Run the executable using `./a.out` (on linux) 
   1) The executable takes a dataset from command line argument. For example, to use an existing dataset, run `./a.out ../datasets/edge.txt`
   2) If no command-line argument is given, it takes input from the shell directly (stdin)

## Input

The required file format for the algorithm to work correctly is:

- First line must contain the no of Points to be taken as input by the program.
- Each of next line must contain 2 integers, space seperated denoting the (x, y) coordinates of each point.
- Each coordinate must be of integer type in the range -2x10^9 to 2x10^9 (long int).
- No of coordinates must be less than 2 Billion.

## Output

--------------------------------TODO:-------------------------
- Write output here
- try input with 0 points
- try manual input
--------------------------------------------------------------

## Documentation and Report

For the report, check the `Report` directory in the parent folder for both pdf and latex formats.

Documentation of this algorithm, functions and classes can be found in the `docs` folder 
in the current directory. Open the [index.html](./docs/index.html) file from the docs directory
with your preferred browser to go through the documentation

## Algorithm Approach

For more detailed information regarding the algorithm, refer to David Mount Lecture notes 
from the course [CMSC 754 - Computational Geometry](https://www.cs.umd.edu/class/spring2020/cmsc754/lectures.html)

Given set of points P, we would like to first order them according to the increasing 
x coordinate. For the sake of simplicity, let us assume that no two points will have
same x or y coordinate and no 3 points are co-linear.

First, we will recursively compute the upper hull and then similarly compute the 
lower hull of the given set of points. Finally, we will join the upper hull with the 
lower hull to complete the convex hull and return/print the clockwise ordering of the
points present on the convex hull
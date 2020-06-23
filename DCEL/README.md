# DCEL - Doubly Connected Edge List

## Introduction



## How to Run

The src folder contains the source code for the convex hull program. `g++` from the GNU
compiler suite is required to compile the program to a executable.

Steps to Compile:

1) `cd` into the src directory
2) Run `g++ main.cpp` which generates an executable called `a.out` in the same directory
3) Run the executable using `./a.out` (on linux) 
   1) The executable takes a dataset from command line argument. For example, to use an existing dataset, run `./a.out ../datasets/4sq.txt`
   2) If no command-line argument is given, it takes input from the shell directly (stdin)

## Input

The required file format for the algorithm to work correctly is:

- First line must contain the no of Edges to be taken as input by the program.
- Each of next line must contain space seperated 4 integers (`x1 y1 x2 y2`) denoting the (x1, y1) (x2, y2) coordinates of endpoints of each edge. (directionality is not required as they are assumed to be undirected)
- Each coordinate must be of integer type in the range -2x10^9 to 2x10^9 (long int).
- No of coordinates must be less than 2 Billion.

## Documentation and Report

For the report, check the `Report` directory in the parent folder for both pdf and latex formats.

Documentation of this algorithm, functions and classes can be found in the `docs` folder 
in the current directory. Open the [index.html](./docs/index.html) file from the docs directory
with your preferred browser to go through the documentation

## Algorithm Approach

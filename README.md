# Computational Geometry Assignment

## Getting Started

This repo contains implementations of the following 3 algorithms:
- **Convex Hull** computation using divide and conquer tangent approach
- **DCEL** (Doubly Connected Edge List) data structure implementation
- **Polygon Triangulation** using the following algorithms:
  - **Plane Sweep** method to divide polygon into monotones.
  - **Triangulation** of each monotone polygon

Each algorithm is implemented seperately in its folder using C++ language. 
A README file in each folder describes how to run and other information about 
that particular folder.

```bash
Algorithm Directory
├── datasets # folder containing datasets to be tested upon
├── docs # folder containing the documentation of the source code
├── src # folder containing the source code
└── README.md # a readme file describing the algo and how to run it
```

## Plotting Output

Each directory contains a `plot.py` python program which can be used to plot the
output of each algorithm. output of algorithm can be directly piped to this program
or given as command line argument

```
# do this in the src directory if program is compiled in the same directory
# the text in the [] brackets is optional. if given, it prints the input dataset also
./a.out ../datasets/data.txt | ../plot [-i ../datasets/data.txt]

# without piping, save output to file and use it
./a.out ../datasets/data.txt > output.txt
../plot -o output.txt [-i ../datasets/data.txt]
```

## References

The following references have been used to understand and implement
the algorithms:
- [David Mount lecture notes](https://www.cs.umd.edu/class/spring2020/cmsc754/lectures.html)
- [DCEL algorithm and basic geometry data-structure conventions](https://cs.stackexchange.com/questions/2450/how-do-i-construct-a-doubly-connected-edge-list-given-a-set-of-line-segments)
- [Understanding DCEL inserting algorithm](https://stackoverflow.com/questions/56980195/adding-edges-dynamically-in-a-dcel-half-edge-based-graph)
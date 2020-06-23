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

------------------------------TODO: Update the tree structure---------------------------
```bash
Algorithm Directory
├── datasets # folder containing datasets to be tested upon
├── docs # folder containing the documentation of the source code
├── src # folder containing the source code
└── README.md # a readme file describing the algo and how to run it
```

## Convex Hull Algo based on Divide & Conquer (Tangent Approach)

- Implementation from David Mount lecture notes
- **Tasks**:
  - [x] verify algo by plotting or running on known points
  - [x] run algo on huge datasets
  - [x] code comments and documentation
  - [x] performance analysis

## Implement DCEL

- **Tasks**:
  - [x] Implement DCEL
  - [ ] run algo on huge datasets
  - [ ] code comments and documentation
  - [ ] performance analysis

## Polygon Triangulation

- **Tasks**:
  - [ ] compare the 2 different algorithms

### Ear Splitting Approach

- Starting point: Wikipedia
- **Tasks**:
  - [ ] run algo on huge datasets
  - [ ] code comments and documentation
  - [ ] performance analysis

### Triangulation based on Monotone Polygons

- David Mount notes
- **Tasks**:
  - [ ] run algo on huge datasets
  - [ ] code comments and documentation
  - [ ] performance analysis

## References

The following references have been used to understand and implement
the algorithms:
- [David Mount lecture notes](https://www.cs.umd.edu/class/spring2020/cmsc754/lectures.html)
- [DCEL algorithm and basic geometry data-structure conventions](https://cs.stackexchange.com/questions/2450/how-do-i-construct-a-doubly-connected-edge-list-given-a-set-of-line-segments)
- [Understanding DCEL inserting algorithm](https://stackoverflow.com/questions/56980195/adding-edges-dynamically-in-a-dcel-half-edge-based-graph)
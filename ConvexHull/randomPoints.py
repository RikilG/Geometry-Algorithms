#!/usr/bin/env python

import os
try:
    from numpy import random
    using_numpy = True
except:
    print("Numpy lib not found. Falling back to defaults")
    using_numpy = False
    import random

MIN = -1e7
MAX = 1e7

def main():
    print("File will be stored in datasets directory with filename as (no-of-points).txt")
    n = int(input("Enter no of points to generate: "))

    filename = str(n) + '.txt'

    points = set()
    xs = set()
    ys = set()

    while len(points) < n:
        x = random.randint(MIN, MAX)/1000
        while x in xs:
            if using_numpy: x = random.normal(0, MAX/100)/1000
            else: x = random.randint(MIN, MAX)/1000
        y = random.randint(MIN, MAX)/1000
        while y in ys:
            if using_numpy: y = random.normal(0, MAX/100)/1000
            else: y = random.randint(MIN, MAX)/1000
        points.add((x, y))
    
    with open("./datasets/"+filename, 'w') as f:
        f.write(f"{len(points)}\n")
        for p in points:
            x, y = p
            f.write(f"{x} {y}\n")


if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(e)
        print("Exiting.")
        exit(1)
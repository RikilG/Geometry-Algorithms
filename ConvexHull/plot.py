#!/usr/bin/env python

import os
import sys
import argparse
import matplotlib.pyplot as plt
from matplotlib.pyplot import Polygon

f, ax = plt.subplots()

def plotPoly(file):
    lines = []
    lines = file.readlines()
    n = int(lines[0].strip());
    xy = []
    xs = []
    ys = []
    for i in range(1, n+1):
        x, y = lines[i].split()
        x, y = int(x), int(y)
        xy.append([x, y])
        xs.append(x)
        ys.append(y)
    pointSize = 2
    if len(xy) < 500: pointSize = 20
    elif len(xy) < 100: pointSize = 35
    plt.scatter(xs, ys, s=pointSize, label="All points")


def main(file):
    x = []
    y = []
    xy = []
    for line in file:
        if not (line[0]=='(' or '0'<=line[0]<='9'): continue
        line = line.replace(',', ' ').replace('(', ' ').replace(')', ' ').split()
        x.append(line[0])
        y.append(line[1])
        xy.append([line[0], line[1]])
    polygon = Polygon(xy, edgecolor='red', fill=None, label="Convex hull")
    ax.add_patch(polygon)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='pipe points to stdin or provide file as argument to plot')
    parser.add_argument('outputFile', nargs='?', default=None, help='optional output to read from file. if provided, -o option is ignored')
    parser.add_argument('-i', '--input', default=None, help='optional input file which has the original polygon')
    parser.add_argument('-o', '--output', default=None, help='optional output file from the program, if not given, stdin is assumed')
    args = parser.parse_args()
    outFile = args.outputFile or args.output
    inFile = args.input
    if outFile == None:
        file = sys.stdin
    else:
        if not os.path.exists(outFile):
            print('provided output filepath is invalid')
            exit(1)
        file = open(outFile, 'r')
    if inFile != None and os.path.exists(inFile):
        inFile = open(inFile, 'r')
    # try:
    main(file)
    if inFile != None: plotPoly(inFile)
    plt.xlabel("X axis")
    plt.ylabel("Y axis")
    plt.title("Computed Convex Hull")
    plt.legend()
    plt.plot()
    plt.show()
    # except Exception as e:
    #     file.close()
    #     if inFile != None: inFile.close()
    #     print(e)
    #     print('Encountered error, quitting...')

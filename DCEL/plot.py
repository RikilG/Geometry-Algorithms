#!/usr/bin/env python

import os
import sys
import random
import argparse
import traceback
import matplotlib.pyplot as plt
from matplotlib.pyplot import Polygon

f, ax = plt.subplots()

def plotPoly(file):
    lines = []
    lines = file.readlines()
    n = int(lines[0].strip().split()[0].strip());
    xy = []
    for i in range(1, n+1):
        coords = [ float(k) for k in lines[i].split() ]
        x1, y1, x2, y2 = coords
        # xy.append([x, y])
        plt.plot([x1, x2], [y1, y2], '--', linewidth=2, color='red')
    # polygon = Polygon(xy, edgecolor='red', facecolor=None, fill=None, linewidth='3')
    # ax.add_patch(polygon)


def main(file):
    xy = []
    for line in file:
        print(line, end='')
        if line == '\n' or line[0] not in ['F', 'H']: continue
        if line[0] == 'F':
            if len(xy) == 0: continue
            polygon = Polygon(xy, color=[ random.uniform(0,1) for _ in range(3) ])
            ax.add_patch(polygon)
            xy = []
            continue
        line = line.replace('HEdge: ', '').replace(' -> ', ' ').replace(',', ' ').replace('(', ' ').replace(')', ' ').split()
        xy.append([line[0], line[1]])
    if len(xy) != 0:
        polygon = Polygon(xy, color=[ random.uniform(0,1) for _ in range(3) ])
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
    try:
        main(file)
        if inFile != None: plotPoly(inFile)
        if inFile != None: print(f"File name: {args.input}")
        plt.plot()
        plt.show()
    except Exception as e:
        file.close()
        if inFile != None: inFile.close()
        print(e)
        print(traceback.format_exc())
        print('Encountered error, quitting...')

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
        x, y = lines[i].split()
        xy.append([x, y])
    polygon = Polygon(xy, edgecolor='red', facecolor=None, fill=None, linewidth='3')
    ax.add_patch(polygon)


def main(file):
    triangles = []
    for line in file:
        print(line, end='')
        if not (line[0]=='(' or '0'<=line[0]<='9'): continue
        line = line.replace(',', ' ').replace('(', ' ').replace(')', ' ').split()
        x = []
        y = []
        xy = []
        for i in range(len(line)):
            line = [float(k) for k in line]
            if i%2==0:
                x.append(line[i])
                y.append(line[i+1])
                xy.append([line[i], line[i+1]])
        triangles.append((x,y))
        polygon = Polygon(xy, color=[random.uniform(0,1) for _ in range(3)])
        # for p in xy:
        #     i_x, i_y = p
        #     plt.text(i_x, i_y, '({}, {})'.format(i_x, i_y))
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
        plt.plot()
        plt.show()
    except Exception as e:
        file.close()
        if inFile != None: inFile.close()
        print(e)
        print(traceback.format_exc())
        print('Encountered error, quitting...')

#!/usr/bin/env python

import os

file = input("Enter path to file which is ccw, to be converted to cw: ")

if not os.path.exists(file):
    print("File does not exist!")
    exit(1)

n = None
lines = []

with open(file, 'r') as f:
    lines = f.readlines()
    n = int(lines[0].strip().split()[0].strip())
    lines = lines[1:]

with open(file, 'w') as f:
    lines = lines[::-1] # reverse the contents to change order
    f.write(f"{n}\n")
    for l in lines:
        f.write(l)

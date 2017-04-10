#!/usr/bin/env python3

steps= 1000
inside= 0

for x in range(steps):
    for y in range(steps):
       if ((x/steps)**2 + (y/steps)**2) < 1:
           inside+= 1

print(inside*4/(steps**2))

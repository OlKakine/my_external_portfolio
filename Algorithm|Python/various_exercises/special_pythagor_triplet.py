#! /usr/bin/env python3

for c in range(333,1000):
    for a in range(0,(1000-c)//2):
        b=1000-c-a
        if a**2+b**2==c**2:
            print(a,b,c,a*b*c)

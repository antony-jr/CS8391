#!/usr/bin/env python3
import sys
from random import randint

if len(sys.argv) == 1:
    print("Usage: {} [NO. OF RANDOM NUMBERS TO GENERATE]".format(sys.argv[0]))
    sys.exit(0)

a = 0
try:
    a = int(sys.argv[1]);
except Exception as e:
    print("3"); # Tell the progrom to exit.
    print(e);
    sys.exit(-1)

for i in range(0 , a):
    print("1"); # Tell the program to insert new node
    print(randint(0 , 2**10)); # Generate a random value and insert it

print("3") # quit the program

#!/usr/bin/env python3
from random import randint
l = [randint(0,10000) for i in range(100)];
l.sort()

print(100);

for i in l:
    print(i)

r = randint(0,99)
print(l[r])
print("The actual index: {}".format(r))

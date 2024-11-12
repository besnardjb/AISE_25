#!/bin/env python3


import json

with open("part.dat", "r") as f:
    data = json.load(f)

for p in data:
    print(f"x : {p['x']} , y : {p['y']} , z : {p['z']}")

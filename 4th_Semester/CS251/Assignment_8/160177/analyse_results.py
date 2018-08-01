#!/usr/bin/env python3

import re

# Getting Files
params_file = "params.txt"
results_file = "runtest"

# Reading params.txt
fd = open(params_file, 'r')
line = fd.readline()
fd.close()
params = line.split(' ')
params[len(params)-1] = params[len(params)-1].strip()

# Reading results.txt
results = {}
fd = open(results_file, 'r')
for num_elements in params:
    thrd = 1
    while (thrd <= 16):
        a = []
        for i in range(0,100):
            line = fd.readline()
            a.append(int(re.findall("[0-9]+", line)[0]))
        results[(num_elements, thrd)] = a
        thrd *= 2

# Generating scatter.out files for each thread
thrd = 1
while (thrd <= 16):
    f = "thread_" + str(thrd) + "_scatter.out"
    fd = open(f, "w")
    for num_elements in params:
        for i in range(0,100):
            fd.write(num_elements + " " + str(results[(num_elements, thrd)][i]) + "\n")
    thrd *= 2
    fd.close()

# Generating thread_lineplot.out file for each thread
f = "thread_lineplot.out"
fd = open(f, "w")
for num_elements in params:
    thrd = 1
    fd.write(num_elements + " ")
    while (thrd <= 16):
        l = results[(num_elements, thrd)]
        avg = sum(l) / len(l)
        fd.write(str(avg) + " ")
        thrd *= 2
    fd.write("\n")
fd.close()

# Generating thread_speedup.out file
f = "thread_speedup.out"
fd = open(f, "w")
for num_elements in params:
    thrd = 1
    base = 1
    fd.write(num_elements + " ")
    while (thrd <= 16):
        l = results[(num_elements, thrd)]
        avg = sum(l) / len(l)
        if (thrd == 1):
            base = avg
        avg = base / avg
        fd.write(str(avg) + " ")
        thrd *= 2
    fd.write("\n")
fd.close()

# Generating thread_errorbars.out file
f = "thread_errorbars.out"
fd = open(f, "w")
for num_elements in params:
    thrd = 1
    base = 1
    fd.write(num_elements + " ")
    while (thrd <= 16):
        l = results[(num_elements, thrd)]
        avg = sum(l) / len(l)
        if (thrd == 1):
            base = avg
        avg = base / avg
        sqsum = 0
        for i in range(0,100):
            sqsum += ((base / l[i]) - avg) ** 2
        var = sqsum / len(l)
        fd.write(str(avg) + " " + str(var) + " ")
        thrd *= 2
    fd.write("\n")
fd.close()

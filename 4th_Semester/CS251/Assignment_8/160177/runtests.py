#!/usr/bin/env python3

import subprocess

# Getting Files
params_file = "params.txt"
threads_file = "threads.txt"

# Reading params.txt
fd = open(params_file, 'r')
line = fd.readline()
fd.close()
params = line.split(' ')
params[len(params)-1] = params[len(params)-1].strip()

# Reading threads.txt
fd = open(threads_file, 'r')
line = fd.readline()
fd.close()
threads = line.split(' ')
threads[len(threads)-1] = threads[len(threads)-1].strip()

for num_elements in params:
    for num_threads in threads:
        cmd = "./App " + num_elements + " " + num_threads
        for i in range(0,100):
            subprocess.call(cmd, shell=True)

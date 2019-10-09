#!/bin/bash

set -e
set -x

make
mv gemOS.kernel binaries/gemOS.kernel
cd ..
build/X86/gem5.opt configs/example/fs.py
cd gemos

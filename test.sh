#!/usr/bin/env bash

sudo rm -rf build &&\
mkdir build &&\
cd build &&\
cmake .. &&\
cmake --build . &&\
ctest -V

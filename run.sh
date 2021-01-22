#!/bin/bash

# to run python is required --- otherwise just use "make" in "./trunk" dir..

# this is a script to run the whole testing part ---
# --- though didn't make tests for python code so it might throw an error when a matrix is singular..

rm sing_list

cd tests

rm -rf results
mkdir results
rm -rf data
mkdir data
make
./main

# didnt 
cd scripts
python make_results.py 100

cd ../../
make
make test

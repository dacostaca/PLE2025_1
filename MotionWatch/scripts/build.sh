#!/bin/bash

BASEDIR=$(dirname "$0")/..
cd "$BASEDIR"

mkdir -p bin frames logs

make clean
make all

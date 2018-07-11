#!/bin/bash

build_directory="build"

mkdir -p $build_directory
cd $build_directory
cmake -g "Unix Makefiles" ..
make -j4

#!/bin/bash

build_directory="build"

tput reset

mkdir -p $build_directory
cd $build_directory
cmake -g "Unix Makefiles" ..
unbuffer make -j$(nproc) | head -n 67

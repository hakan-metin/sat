#! /bin/bash
# Build googletest library used for testing solver
# Prerequisite: make submodules


if ! [[ -d third_party/googletest/ ]]; then
    git clone https://github.com/google/googletest.git third_party/gtest
    cd third_party/gtest
    git checkout release-1.8.0
    cd -
fi

LIB_DIR='third_party/gtest/googletest/build/'

if [[ -e "$LIB_DIR"libgtest.a ]] && [[ -e "$LIB_DIR"libgtest_main.a ]]; then
    exit 0
fi

mkdir -p "$LIB_DIR"
cd "$LIB_DIR"
cmake ..
make
cd -

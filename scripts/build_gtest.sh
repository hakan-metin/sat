#! /bin/bash
# Build googletest library used for testing solver

if ! [[ -d third_party/gtest ]]; then
    git clone https://github.com/google/googletest.git third_party/gtest
fi

GTEST_DIR="third_party/gtest/googletest/"

if ! [[ -e "$GTEST_DIR"libgtest.a ]]; then
    g++ -isystem $GTEST_DIR/include -I${GTEST_DIR} \
        -pthread -c ${GTEST_DIR}/src/gtest-all.cc -o ${GTEST_DIR}/gtest-all.o
    ar -rv ${GTEST_DIR}/libgtest.a ${GTEST_DIR}/gtest-all.o
fi

if ! [[ -e "$GTEST_DIR"libgtest_main.a ]]; then
    g++ -isystem $GTEST_DIR/include -I${GTEST_DIR} \
        -pthread -c ${GTEST_DIR}/src/gtest_main.cc -o ${GTEST_DIR}/gtest_main.o
    ar -rv ${GTEST_DIR}/libgtest_main.a ${GTEST_DIR}/gtest_main.o
fi

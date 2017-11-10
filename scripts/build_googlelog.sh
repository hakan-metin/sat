#! /bin/bash
# Build googlelog library used for logging


if ! [[ -d third_party/glog ]]; then
    git clone https://github.com/google/glog.git third_party/glog
    cd third_party/glog
    git checkout v0.3.5
    cd -
fi


LIB_DIR='third_party/glog/build/'

if [[ -e "$LIB_DIR"libglog.a ]] ; then
    exit 0
fi

mkdir -p "$LIB_DIR"
cd "$LIB_DIR"
cmake ..
make
cd -

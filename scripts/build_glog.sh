#! /bin/bash
# Build googlelog library used for logging


if ! [[ -d third_party/glog ]]; then
    git clone https://github.com/google/glog.git third_party/glog
    cd third_party/glog
    cd -
fi


LIB_DIR='third_party/glog/'

if [[ -e "$LIB_DIR"lib/libglog.a ]] ; then
    exit 0
fi


cd "$LIB_DIR"
./autogen.sh && ./configure --prefix=$PWD && make && make install
cd -

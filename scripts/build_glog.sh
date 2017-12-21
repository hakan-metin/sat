#! /bin/bash
# Build googlelog library used for logging


GLOG_DIR='third_party/glog/'

if ! [[ -d "${GLOG_DIR}" ]]; then
    git clone https://github.com/google/glog.git "${GLOG_DIR}"
fi

if ! [[ -e "${GLOG_DIR}"lib/libglog.a ]] ; then
    cd "${GLOG_DIR}"
    ./autogen.sh && ./configure --prefix=$PWD && make && make install
    cd -
fi

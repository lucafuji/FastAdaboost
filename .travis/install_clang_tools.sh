#!/usr/bin/env bash
set -ex
# install google test
output_dir=./build
rm -rf /tmp/googletest
git clone -b release-1.8.1 --single-branch https://github.com/google/googletest.git /tmp/googletest
pushd .
cd /tmp/googletest

# build makefile
cmake CMakeLists.txt
make
popd
mv /tmp/googletest ${output_dir}

# install boost
sudo apt-get install libboost-all-dev
#!/bin/zsh

cd $(dirname $(readlink -f "$0"))
rm -rf build
mkdir build && cd build
cmake ..
make
sudo make install

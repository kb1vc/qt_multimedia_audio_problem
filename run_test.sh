#!/bin/bash

if [ ! -f build_qt5 ] ; then
    mkdir build_qt5
    pushd build_qt5
else
    pushd build_qt5    
    rm -rf *
fi

cmake ../qt5_source/
make

popd

if [ ! -f build_qt6 ] ; then
    mkdir build_qt6
    cd build_qt6
else
    cd build_qt6    
    rm -rf *
fi

cmake ../qt6_source/
make

popd

# setup a fake device that should show up as an
# output device "TESTQT" but also as an input device
# "TESTQT.mon"
pactl load-module module-null-sink sink_name=TESTQT sink_properties=device.description="TESTQT"

echo "List audio devices: Qt5"
./build_qt5/cons5_audiodevices

echo "List audio devices: Qt6"
./build_qt6/cons6_audiodevices

echo "Here's what aplay thinks:"
aplay -L


#!/bin/bash

#gn gen out/arm64-debug --root=src --args='target_os="android" target_cpu="arm64" is_debug=true use_custom_libcxx=false treat_warnings_as_errors=false rtc_include_tests=false rtc_use_h264=true'

#ninja -C out/arm64-debug

SOURCE_DIR=$1
INCLUDE_DIR=$2

if [ ! $1 ]; then
	echo "set src dir path"
	exit 1
fi

if [ ! $2 ]; then
	echo "set include dir path"
	exit 1
fi

echo "mkdir $INCLUDE_DIR"
mkdir -p $INCLUDE_DIR
cd $SOURCE_DIR

find api audio base call common_audio common_video logging media \
modules net p2p pc rtc_base rtc_tools sdk stats system_wrappers \
third_party/abseil-cpp third_party/jsoncpp/source/include \
video -name "*.h" \
-exec cp --parents '{}' $INCLUDE_DIR ';'
#find . -maxdepth 1 -name "*.h" -exec cp --parents '{}' $INCLUDE_DIR ';'

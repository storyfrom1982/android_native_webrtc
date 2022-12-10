#!/bin/bash -e

WORK_DIR=$(pwd)

echo $WORK_DIR

#echo 'target_os = ["android", "unix"]' >> .gclient

#gclient sync -r dc5cf31cad576376abd3aa6306169453cfd85ba5

#cd $WORK_DIR/src
#git checkout -b M105 refs/remotes/branch-heads/5195

#$WORK_DIR/src/build/install-build-deps-android.sh

cd $WORK_DIR/src/third_party/libsrtp
git reset --hard @{u}
git checkout main
git reset --hard 5b7c744eb8310250ccc534f3f86a2015b3887a0
git apply --stat $WORK_DIR/patch/0001-libsrtp-m105-5b7c744eb8310250ccc534f3f86a2015b3887a0.patch
git apply --check $WORK_DIR/patch/0001-libsrtp-m105-5b7c744eb8310250ccc534f3f86a2015b3887a0.patch
git am $WORK_DIR/patch/0001-libsrtp-m105-5b7c744eb8310250ccc534f3f86a2015b3887a0.patch

cd $WORK_DIR/src/build
git reset --hard @{u}
git checkout main
git reset --hard bed2979286743b965832101fd1632e0b043f2
git apply --stat $WORK_DIR/patch/0001-src-build-m105-bed2979286743b965832101fd1632e0b043f2.patch
git apply --check $WORK_DIR/patch/0001-src-build-m105-bed2979286743b965832101fd1632e0b043f2.patch
git am $WORK_DIR/patch/0001-src-build-m105-bed2979286743b965832101fd1632e0b043f2.patch

cd $WORK_DIR/src/buildtools
git reset --hard @{u}
git checkout main
git reset --hard d4d55fbf055779487e1b342916c4b12cad65
git apply --stat $WORK_DIR/patch/0001-buildtools-m105-d4d55fbf055779487e1b342916c4b12cad65.patch
git apply --check $WORK_DIR/patch/0001-buildtools-m105-d4d55fbf055779487e1b342916c4b12cad65.patch
git am $WORK_DIR/patch/0001-buildtools-m105-d4d55fbf055779487e1b342916c4b12cad65.patch

cd $WORK_DIR/src
git reset --hard @{u}
git checkout M105
git reset --hard dc5cf31cad576376abd3aa6306169453cfd85ba5
git apply --stat $WORK_DIR/patch/0001-src-m105-dc5cf31cad576376abd3aa6306169453cfd85ba5.patch
git apply --check $WORK_DIR/patch/0001-src-m105-dc5cf31cad576376abd3aa6306169453cfd85ba5.patch
git am $WORK_DIR/patch/0001-src-m105-dc5cf31cad576376abd3aa6306169453cfd85ba5.patch

cd $WORK_DIR
gn gen out/arm64-debug --root=src --args='target_os="android" target_cpu="arm64" is_debug=true rtc_build_examples=false is_component_build=false use_custom_libcxx=false treat_warnings_as_errors=false rtc_include_tests=false rtc_use_h264=true rtc_build_ssl=false rtc_ssl_root="'${WORK_DIR}'/openssl"'
ninja -C out/arm64-debug

$WORK_DIR/scripts/copy_headers.sh $WORK_DIR/src $WORK_DIR/out/include

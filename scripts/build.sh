#!/bin/bash

REPO_DIR=$(git rev-parse --show-toplevel)
REPO_NAME=$(basename $REPO_DIR)
THIS=$(echo $(realpath $0) | sed "s|$REPO_DIR|$REPO_NAME|g")

echo $THIS
echo ----------

set -eux

main() {

    SOURCE_DIR=$REPO_DIR
    BUILD_DIR=$REPO_DIR/.build
    INSTALL_DIR=$REPO_DIR/.install

    cmake \
        -G Ninja \
        -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" \
        -DBUILD_EXAMPLES=ON \
        -B "$BUILD_DIR" \
        "$SOURCE_DIR"

    cmake --build "$BUILD_DIR"
    cmake --install "$BUILD_DIR"

}

main "$@"

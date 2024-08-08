#!/bin/sh

set -e

cd "$(dirname "$0")"/..

. ci/commons.sh

message "Preparing a developement environment..."
mkdir -p build
(cd build && cmake -DAVL_DEVELOPER=ON -DCMAKE_BUILD_TYPE=Asan ..)

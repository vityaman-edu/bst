#!/bin/sh

set -e

cd "$(dirname "$0")"/..

. ci/commons.sh

MODE=$1
if [ -z "$MODE" ]; then
  MODE="Release"
fi

if [ "$MODE" != "Asan" ] && [ "$MODE" != "Release" ]; then
  error "Invalid argument. Must be either 'Asan' or 'Release'."
  exit 1
fi

message "Preparing a developement environment..."
mkdir -p build
(cd build && cmake -DAVL_DEVELOPER=ON -DCMAKE_BUILD_TYPE=$MODE ..)

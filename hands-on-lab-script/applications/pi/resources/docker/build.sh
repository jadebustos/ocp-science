#!/bin/bash
IMAGE_NAME=${IMAGE_NAME:-$1}
IMAGE_TAG=${IMAGE_TAG:-$2}

HTTP_PROXY=${HTTP_PROXY:-$3}

BUILD_ARG=""

if [ ! -z "${HTTP_PROXY}" ]; then
  BUILD_ARG="--build-arg http_proxy=${HTTP_PROXY}"
  BUILD_ARG="${BUILD_ARG} --build-arg https_proxy=${HTTP_PROXY}"
  BUILD_ARG="${BUILD_ARG} --build-arg no_proxy=180.14.131.80,.bsch,.cluster.local,.corp,.local,.novalocal"

  echo "BUILD_ARG=${BUILD_ARG}"
fi

echo "Building backup docker image .."

docker build --no-cache=true ${BUILD_ARG} -t ${IMAGE_NAME}:${IMAGE_TAG} --network host .
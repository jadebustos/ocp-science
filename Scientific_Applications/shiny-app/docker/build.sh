#!/bin/bash
FILEPATH=$(readlink -f $0)
BASEDIR=${FILEPATH%/*}

#IMAGE_REGISTRY=${IMAGE_REGISTRY:-$1}
#IMAGE_LIBRARY=${IMAGE_LIBRARY:-$2}
#IMAGE_REPOSITORY=${IMAGE_REPOSITORY:-$3}
#IMAGE_TAG=${IMAGE_TAG:-$4}
#IMAGE_FULL_TAG=${IMAGE_REGISTRY}/${IMAGE_LIBRARY}/${IMAGE_REPOSITORY}:${IMAGE_TAG}
IMAGE_NAME=${IMAGE_NAME:-$1}
IMAGE_TAG=${IMAGE_TAG:-$2}

HTTP_PROXY=${HTTP_PROXY:-$3}

BUILD_ARG=""

if [ ! -z ${HTTP_PROXY} ]; then
  BUILD_ARG="${BUILD_ARG} --build-arg http_proxy=${HTTP_PROXY}"
  BUILD_ARG="${BUILD_ARG} --build-arg https_proxy=${HTTP_PROXY}"
  BUILD_ARG="${BUILD_ARG} --build-arg no_proxy=180.14.131.80,.bsch,.cluster.local,.corp,.local,.novalocal"
fi

echo "Building backup docker image .."

docker build --no-cache=true ${BUILD_ARG} -t ${IMAGE_NAME}:${IMAGE_TAG} --network host .
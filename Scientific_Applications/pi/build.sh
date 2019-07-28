#!/bin/bash
IMAGE_NAME=${IMAGE_NAME:-$1}
IMAGE_TAG=${IMAGE_TAG:-$2}

echo "Building backup docker image .."

#docker build --no-cache=true --build-arg BASE_CONTAINER=${BUILD_ARG} -t ${IMAGE_NAME}:${IMAGE_TAG} --network host -f ./docker/Dockerfile ./docker
docker build --no-cache=true -t ${IMAGE_NAME}:${IMAGE_TAG} --network host -f ./docker/Dockerfile ./docker
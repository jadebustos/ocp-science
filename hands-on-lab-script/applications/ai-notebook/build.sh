#!/bin/bash
IMAGE_NAME=${IMAGE_NAME:-$1}
IMAGE_TAG=${IMAGE_TAG:-$2}

BUILD_ARG="ubuntu:bionic-20190612@sha256:9b1702dcfe32c873a770a32cfd306dd7fc1c4fd134adfb783db68defc8894b3c"

echo "Building backup docker image .."

#docker build --no-cache=true --build-arg BASE_CONTAINER=${BUILD_ARG} -t ${IMAGE_NAME}:${IMAGE_TAG} --network host -f ./docker/Dockerfile ./docker
docker build --no-cache=true -t ${IMAGE_NAME}:${IMAGE_TAG} --network host -f ./docker/Dockerfile ./docker
#!/bin/bash 

REPO="alibelow"
IMAGE="gcc6-cmake3.12.4"
TAG="cpp-stlcontainers"

# Command to build docker container
if [ "$1" == "build" ]
then
    docker build --build-arg UID=$(id -u) \
                 --build-arg GID=$(id -g) \
                 --build-arg UNAME=$(id -un) \
                 --tag ${REPO}/${IMAGE}:${TAG} \
                 --no-cache=true \
                 -f Dockerfile .
    exit
fi

# Command to run container with entrypoint project.sh script
if [ "$1" == "run" ]
then
    docker run -it --entrypoint ./project.sh ${REPO}/${IMAGE}:${TAG} $2
    exit
fi

# Command to run container with bash
if [ "$1" == "bash" ]
then
    docker run -it ${REPO}/${IMAGE}:${TAG} bash
fi
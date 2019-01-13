#!/bin/bash

# Build function
function build() {
    echo -e "\n*****************************************"
    echo "Building cpp-stlcontainers"
    echo -e "*****************************************"
    # rm -rd build
    # rm -rdf googletest

    mkdir -p build
    cd build
    cmake ..
    make
    cd ..
}

# Run unit tests function
function run_tests() {
    echo -e "\n*****************************************"
    echo "Running cpp-stlcontainer unit tests"
    echo -e "*****************************************"
    ./build/bin/cpp-stlcontainer_unittests
}

# Run main executable
# function run() {
#     echo "Running cpp-stlcontainer"
#     ./build/bin/cpp-container
# }

# If user entry './project.sh build'
if [ "$1" == "build" ]
then
    build
    exit
fi

# If user entry './project.sh test'
if [ "$1" == "test" ]
then
    build
    run_tests
    exit
fi

# If user entry './project.sh run'
# if [ "$1" == "run" ]
# then
    # build
    # run_tests
    # run
    # exit
# fi
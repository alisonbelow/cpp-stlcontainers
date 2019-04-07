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
    echo -e "\n***** VECTOR *****"
    ./build/bin/cpp-stlcontainer_unittests_vector
    echo -e "\n***** STRING *****"
    ./build/bin/cpp-stlcontainer_unittests_string
    echo -e "\n***** STACK *****"
    ./build/bin/cpp-stlcontainer_unittests_stack
    echo -e "\n***** QUEUE *****"
    ./build/bin/cpp-stlcontainer_unittests_queue
}

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
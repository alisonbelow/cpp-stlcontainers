[![Build Status](https://travis-ci.com/alisonbelow/cpp-stlcontainers.svg?branch=master)](https://travis-ci.com/alisonbelow/cpp-stlcontainers) [![Coverage Status](https://coveralls.io/repos/github/alisonbelow/cpp-stlcontainers/badge.svg?branch=master)](https://coveralls.io/github/alisonbelow/cpp-stlcontainers?branch=master)  

# C++ STL Containers

## Background

Inspired by [cplusplus-containers](https://github.com/TusharChugh/cplusplus-containers)  
The purpose of this repository is to exercise and practice C++ programming skills by writing STL Containers.  

## Dependencies

This project requires cmake >= 3.10 and gcc/g++ >= 6 or docker (latest or stable). If you do not wish to install the appropriate versions of cmake/gcc on your own machine, you can build, run, and test the project with the docker image. Then you must only install docker (steps below).  

Docker Install:

```bash
# docker
sudo apt-get remove docker docker-engine docker.io
sudo apt-get update
sudo apt-get install apt-transport-https ca-certificates curl software-properties-common
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo apt-key fingerprint 0EBFCD88
sudo add-apt-repository    "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
   $(lsb_release -cs) \
   stable"
sudo apt-get update
sudo apt-get install docker-ce
sudo docker run hello-world

# Add your user to docker group to use with non-sudo access
sudo groupadd docker
sudo usermod -aG docker $USER

# Log in and out for changes to take effect
docker run hello-world
```

GCC/G++ Install:  

```bash
# gcc/g++
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install gcc-6
sudo apt install g++-6
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6
```

cmake Install:

```bash
# cmake
wget https://cmake.org/files/v3.12/cmake-3.12.4.tar.gz
tar -xvzf cmake-3.12.4.tar.gz
cd cmake-3.12.4
./configure
make
sudo make install
sudo update-alternatives --install /usr/bin/cmake cmake /usr/local/bin/cmake 1 --force
cmake --version
```

## Building

### Building in Docker (Recommended)

The suggest approach is to build with the docker container.

- Install Docker as described above
- Clone this repository
- Build the docker image from the Dockerfile. This will create a docker image called alibelow/gcc6-cmake.3.12.4
- Run docker container and execute build command

```sh
git clone https://github.com/alisonbelow/cpp-stlcontainers.git
cd cpp-stlcontainers

# Build docker image
./docker.sh build

# Run docker container and execute build command
./docker.sh run build
```

### Building on local

If you wish to install the dependencies and build on your local machine, clone the repository and run the project.sh script with the argument `build`.

```sh
git clone https://github.com/alisonbelow/cpp-stlcontainers.git
cd cpp-stlcontainers

# Run project shell script with build argument
./project.sh build
```

## Test

Test executables are created in the build/bin directory. Simply execute `cpp-stlcontainer_unittests` to run GTests. More tests can be added in the `test` directory, in the appropriate folder for each container.  

### Testing in Docker (recommended)

Run the docker container and execute test command. This scripted option will *build* and then test.

```sh
./docker.sh run test
```

### Testing on local

Run the test command using the project.sh script with the argument `test`.

```sh
./project.sh test
```

#!/bin/bash

## This script can be used to build on Linux.
## You need to have CMake installed.
## If you want to build on Windows, you need to install a bash interpreter like Git Bash.

function say() {
    echo -e "(._.) <( \x1b[34;1m" $@ "\x1b[m )"
}

function err() {
    echo -e "(x.x) <( \x1b[31;1m" $@ "\x1b[m )"
}

function exportPath() {
    export JEPGO_BUILD="$(pwd)/build"
    export JEPGO_INCLUDE="$(pwd)/include"
}

function build() {
    exportPath;
    [[ ! -d "build" ]] && say "Creating build folder" && mkdir build;
    say "Going to the build directory";
    cd build/;
    say "CMaking";
    cmake ..
    say "Building files";
    cmake --build .
    if [[ $? -ne 0 ]]; then
        err "Error while compiling"
    fi
    say "Going back";
    cd ..
}

function fclean() {
    say "Removing build directory."
    rm -rf build/
    if [[ $? -ne 0 ]]; then
        say "Failed to remove build directory"
        exit 84
    fi
    say "Build directory removed."
}

if [[ $1 == "path" ]]; then
    exportPath;
    exit 0;
fi

if [[ $1 == "fclean" ]]; then
    fclean
    exit 0
fi

if [[ $1 == "re" ]]; then
    fclean
fi

build;

# if [[ -d "build" ]]; then
#     echo -e "\e[32mBuild directory already created.\e[0m"
# else
#     echo -e "\e[33mNo build directory found, creating new one.\e[0m"
#     mkdir build;
#     if [[ $? -ne 0 ]]; then
#         echo -e "\e[31mFailed to create build directory.\e[0m"
#         exit 1
#     fi
#     echo -e "\e[32mBuild directory created.\e[0m"
# fi

# echo -e "\e[33mGoing to build directory.\e[0m"
# cd build;
# if [[ $? -ne 0 ]]; then
#     echo -e "\e[31mFailed to change to build directory.\e[0m"
#     exit 1
# fi

# echo -e "\e[33mLaunching cmake.\e[0m"
# cmake ../;
# if [[ $? -ne 0 ]]; then
#     echo -e "\e[31mFailed to run cmake.\e[0m"
#     exit 1
# fi
# echo -e "\e[32mCMake finished.\e[0m"

# echo -e "\e[33mBuilding targets.\e[0m"
# cmake --build .
# if [[ $? -ne 0 ]]; then
#     echo -e "\e[31mFailed to build targets.\e[0m"
#     exit 1
# fi
# echo -e "\e[32mTargets built.\e[0m"

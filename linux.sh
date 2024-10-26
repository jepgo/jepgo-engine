#!/bin/bash

## This script can be used to build on Linux.
## You need to have CMake installed.
## If you want to build on Windows, you need to install a bash interpreter like Git Bash.

fclean() {
    echo -e "\e[33mRemoving build directory.\e[0m"
    rm -rf build
    if [[ $? -ne 0 ]]; then
        echo -e "\e[31mFailed to remove build directory.\e[0m"
        exit 1
    else 
        echo -e "\e[32mBuild directory removed.\e[0m"
    fi
}

if [[ $1 == "fclean" ]]; then
    fclean
    exit 0
fi

if [[ $1 == "re" ]]; then
    fclean
fi

if [[ -d "build" ]]; then
    echo -e "\e[32mBuild directory already created.\e[0m"
else
    echo -e "\e[33mNo build directory found, creating new one.\e[0m"
    mkdir build;
    if [[ $? -ne 0 ]]; then
        echo -e "\e[31mFailed to create build directory.\e[0m"
        exit 1
    fi
    echo -e "\e[32mBuild directory created.\e[0m"
fi

echo -e "\e[33mGoing to build directory.\e[0m"
cd build;
if [[ $? -ne 0 ]]; then
    echo -e "\e[31mFailed to change to build directory.\e[0m"
    exit 1
fi

echo -e "\e[33mLaunching cmake.\e[0m"
cmake ../;
if [[ $? -ne 0 ]]; then
    echo -e "\e[31mFailed to run cmake.\e[0m"
    exit 1
fi
echo -e "\e[32mCMake finished.\e[0m"

echo -e "\e[33mBuilding targets.\e[0m"
cmake --build .
if [[ $? -ne 0 ]]; then
    echo -e "\e[31mFailed to build targets.\e[0m"
    exit 1
fi
echo -e "\e[32mTargets built.\e[0m"

# echo -e "\e[33mCopying files.\e[0m"
# unameOut="$(uname -o)"
# if [[ $unameOut == "Msys" ]]; then
#     cp Debug/r-type* ../
#     cp Debug/libjep* ../
# elif [[ $unameOut == "GNU/Linux" ]]; then
#     cp r-type* ../
#     cp libjep* ../
# fi
# if [[ $? -ne 0 ]]; then
#     echo -e "\e[31mFailed to copy files.\e[0m"
#     exit 1
# fi
# echo -e "\e[32mFiles copied.\e[0m"
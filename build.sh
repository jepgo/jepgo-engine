#!/bin/bash

if [[ $1 == "fclean" ]] || [[ $1 == "re" ]]; then
    rm -rf build r-type_server r-type_client;
fi

if [[ $1 == "fclean" ]]; then
    exit 0 ;
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

echo -e "\e[33mLaunching R-TYPE build.\e[0m"
cmake ../;
if [[ $? -ne 0 ]]; then
    echo -e "\e[31mFailed to run cmake.\e[0m"
    exit 1
fi
echo -e "\e[32mMakefile created.\e[0m"

echo -e "\e[33mLaunching make.\e[0m"
make ;
if [[ $? -ne 0 ]]; then
    echo -e "\e[31mFailed to run make.\e[0m"
    exit 1
fi
echo -e "\e[32mMake done.\e[0m"

echo -e "\e[33mCopying files.\e[0m"
cp r-type* ../
# cp libjepgo.a ../
# cp libjepgame.a ../
if [[ $? -ne 0 ]]; then
    echo -e "\e[31mFailed to copy files.\e[0m"
    exit 1
fi
echo -e "\e[32mFiles copied.\e[0m"
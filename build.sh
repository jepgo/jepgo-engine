#!/bin/bash

if [[ $1 == "fclean" ]] || [[ $1 == "re" ]]; then
    rm -rf build r-type_server r-type_client;
fi

if [[ $1 == "fclean" ]]; then
    exit 0 ;
fi

mkdir build ;
cd build ;
cmake .. ;
make ;
cp r-type_* libjepgo.a libjepgame.a ../;

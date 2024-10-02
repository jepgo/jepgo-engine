#include <iostream>
#include "jepmod/DLLoader.hpp"

int main(void)
{
    jmod::DLLoader loader("./caca.so");
    auto foo = loader.getFunc<int>("foo");

    std::cout << foo() << std::endl;
    return 0;
}

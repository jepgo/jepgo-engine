#include <iostream>
#include "jepmod/DLLoader.hpp"
#include "jepmod/Jepmodule.hpp"

int main(void)
{
    // jmod::DLLoader loader("./caca.so");
    // auto foo = loader.getFunc<int>("foo");

    // std::cout << foo() << std::endl;

    jmod::Jepmodule m("basic");
    return 0;
}

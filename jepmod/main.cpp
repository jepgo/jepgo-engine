#include <iostream>
#include "jepmod/DLLoader.hpp"
#include "jepmod/Jepmodule.hpp"

int main(void)
{
    jmod::DLLoader loader("zizi");
    auto foo = loader.getFunc<int, int, int>("foo");

    std::cout << foo(2, 3) << std::endl;

    // jmod::Jepmodule m("basic");
    return 0;
}

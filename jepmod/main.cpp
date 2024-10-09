#include <iostream>
#include "jepmod/DLLoader.hpp"
#include "jepmod/Jepmodule.hpp"

int main(void)
{
    jmod::DLLoader loader("C:\\Users\\John\\source\\repos\\R-Type\\build\\Debug\\zizi.dll");
    auto foo = loader.getFunc<int, int, int>("foo");

    std::cout << foo(2, 3) << std::endl;

    // jmod::Jepmodule m("basic");
    return 0;
}

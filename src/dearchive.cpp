#include "dearchive.h"
#include "utilities.h"

#include <iostream>

void Dearchive(const char* archive) {
    BitIstream<std::ifstream> in(archive);

    Byte9 x(0);
    x.Read(in);
    std::cout << x.Get() << "\n";
    x.Read(in);
    std::cout << x.Get() << "\n";
    x.Read(in);
    std::cout << x.Get() << "\n";
    x.Read(in);
    std::cout << x.Get() << "\n";
    x.Read(in);
    std::cout << x.Get() << "\n";

    // for (int i = 0; i < 8; i++) {
    //     bool r;
    //     in >> r;
    //     std::cout << r << " ";
    // }
}
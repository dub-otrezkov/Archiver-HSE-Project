#include <iostream>
#include <fstream>

#include "archive.h"
#include "dearchive.h"

#include "utilities.h"

int main(int argc, char** arg) {
    std::vector<const char*> names = {"Hello.txt"};

    // Archive("D:\\GitHub\\Archiver-HSE-Project\\src\\out.txt", names);
    Dearchive("D:\\GitHub\\Archiver-HSE-Project\\src\\out.txt");

    // std::ifstream goyda("D:\\GitHub\\Archiver-HSE-Project\\src\\out.txt");

    // for (;;) {
    //     goyda.peek();
    //     if (goyda.eof()) {
    //         break;
    //     }
    //     char x;
    //     goyda.get(x);
    //     auto t = Byte9(x).Get();
    //     t.pop_back();
    //     std::reverse(t.begin(), t.end());
    //     // std::cout << t;
    //     std::cout << t << "\n";
    // }
}
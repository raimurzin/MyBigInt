#include "BigInt.h"
#include <iostream>

int main() {
    BigInt a("13");
    BigInt b("65");
    b /= a;
    std::cout << a % b << std::endl;
    return 0;
}

#include <iostream>
#include "calculator.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    calculator cal("3+2-5");
    std::cout << cal.result();
    return 0;
}

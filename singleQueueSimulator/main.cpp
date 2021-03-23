#include "simulator.h"
#include <iostream>

int main() {
    simulator s;
    std::cout << "Average wait time: " << s.average_wait_time();
    return 0;
}

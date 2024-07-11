#include <iostream>
#include "Test.h"

int main(int argc, char **argv) {
    std::cout << "beginning..." << std::endl;
    Test *t = new Test();
    t->init(argc, argv);
    t->compute();
    std::cout << t->result()[0] << std::endl;
    delete t;
    return 0;
}

#include <iostream>
#include "Test.h"

int main(int argc, char **argv) {
    std::cout << "beginning..." << std::endl;
    Test *t = new Test();
    t->init(argc, argv);
    std::cout << t->result() << std::endl;
    delete t;
    return 0;
}

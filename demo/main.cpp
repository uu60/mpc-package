#include <iostream>
#include "Test.h"

int main(int argc, char **argv) {
    std::cout << "beginning..." << std::endl;
    Test::initMPI(argc, argv);
    Test *t = new Test();
    t->init();
    t->compute();
    std::cout << t->result() << std::endl;
    Test::finalizeMPI();
    std::cout << "done" << std::endl;
    delete t;
    return 0;
}

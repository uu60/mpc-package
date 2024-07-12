#include <iostream>
#include "Test.h"
#include <string>
#include "./mpc_package/utils/Log.h"

int main(int argc, char **argv) {
    Log::e("beginning");
    Test::initMPI(argc, argv);
    Test *t = new Test();
    t->init();
    t->compute();
    std::cout << t->result() << std::endl;
    Test::finalizeMPI();
    Log::i("done");
    delete t;
    return 0;
}

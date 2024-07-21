#include <iostream>
#include <string>
#include "./mpc_package/utils/Log.h"
#include "./mpc_package/utils/MpiUtils.h"
#include "./mpc_package/ot/one_of_two/RsaExecutor.h"

int main(int argc, char **argv) {
    Log::e("beginning");
    MpiUtils::initMPI(argc, argv);
    auto *r = new RsaExecutor(0, 10, 20, 0);
    Log::i("r inited");
    r->compute();
    Log::i("r computed");
    Log::i(std::to_string(r->result()));
    MpiUtils::finalizeMPI();
    return 0;
}

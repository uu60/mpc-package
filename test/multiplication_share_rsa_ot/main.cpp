#include <iostream>
#include <string>
#include "mpc_package/utils/Log.h"
#include "mpc_package/utils/MpiUtils.h"
#include "mpc_package/utils/MathUtils.h"
#include "mpc_package/executor/share/arithmetic/RsaOtMultiplicationShareExecutor.h"

int main(int argc, char **argv) {
    MpiUtils::initMPI(argc, argv);
    Log::i("Beginning...");
    int a = MathUtils::rand32();
    Log::i("Multiplier: " + std::to_string(a));
    RsaOtMultiplicationShareExecutor m(a, 32);
    m.setBenchmark(true);
    m.compute();
    Log::i(std::to_string((m.getResult())));
    Log::i("Done.");
    MpiUtils::finalizeMPI();
    return 0;
}

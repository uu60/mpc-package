#include "mpc_package/utils/Log.h"
#include "mpc_package/utils/MpiUtils.h"
#include "test_cases.h"

int main(int argc, char **argv) {
    MpiUtils::initMPI(argc, argv);
    Log::i("Beginning...");

    test_XorBooleanShareExecutor();

    Log::i("Done.");
    MpiUtils::finalizeMPI();
    return 0;
}


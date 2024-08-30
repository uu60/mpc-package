#include "mpc_package/utils/Log.h"
#include "mpc_package/utils/MpiUtils.h"
#include "test_cases.h"

int main(int argc, char **argv) {
    MpiUtils::init(argc, argv);
    Log::i("Beginning...");

    test_AndBoolShareExecutor();

    Log::i("Done.");
    MpiUtils::finalize();
    return 0;
}


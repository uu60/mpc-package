//
// Created by 杜建璋 on 2024/8/29.
//

#include "boolean/xor/XorShareExecutor.h"
#include "utils/Mpi.h"

XorShareExecutor::XorShareExecutor(bool x) : BoolShareExecutor(x) {

}

XorShareExecutor::XorShareExecutor(bool x, bool y) : BoolShareExecutor(x, y) {}

XorShareExecutor* XorShareExecutor::execute(bool reconstruct) {
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    int64_t start = System::currentTimeMillis();
    if (Mpi::isServer()) {
        _zi = _xi ^ _yi;
        _result = _zi;
    }
    if (reconstruct) {
        this->reconstruct();
    }
    if (_benchmarkLevel >= Executor::BenchmarkLevel::GENERAL && _isLogBenchmark) {
        _entireComputationTime = System::currentTimeMillis() - start;
        if (_isLogBenchmark) {
            if (detailed) {
                Log::i(tag(),
                       "Mpi synchronization and transmission time: " + std::to_string(_mpiTime) + " ms.");
            }
            Log::i(tag(), "Entire computation time: " + std::to_string(_entireComputationTime) + " ms.");
        }
    }
    return this;
}

std::string XorShareExecutor::tag() const {
    return "[XOR Boolean Share]";
}

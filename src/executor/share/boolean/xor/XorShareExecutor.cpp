//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/xor/XorShareExecutor.h"
#include "utils/Mpi.h"

XorShareExecutor::XorShareExecutor(bool x, bool y) : AbstractBoolShareExecutor(x, y) {}

XorShareExecutor* XorShareExecutor::execute(bool reconstruct) {
    bool detailed = _benchmarkLevel == BenchmarkLevel::DETAILED;
    int64_t start = System::currentTimeMillis();
    if (Mpi::isCalculator()) {
        _zi = _xi xor _yi;
        _result = _zi;
    }
    if (reconstruct) {
        this->reconstruct();
    }
    if (_benchmarkLevel >= AbstractExecutor::BenchmarkLevel::GENERAL && _isLogBenchmark) {
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

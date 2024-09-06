//
// Created by 杜建璋 on 2024/7/13.
//

#include "executor/share/arithmetic/multiplication/AbstractMultiplicationShareExecutor.h"
#include "utils/Mpi.h"
#include "utils/Math.h"
#include "utils/Log.h"

AbstractMultiplicationShareExecutor::AbstractMultiplicationShareExecutor(int64_t x, int l) {
    // data
    _x = x;
    _x1 = Math::rand64();
    _x0 = _x - _x1;

    _l = l >= 64 ? 64 : (l >= 32 ? 32 : (l >= 16 ? 16 : (l >= 8 ? 8 : 4)));
}

void AbstractMultiplicationShareExecutor::compute() {
    int64_t start, end, end1;
    if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
        start = System::currentTimeMillis();
    }
    if (Mpi::isCalculator()) {
        // MT
        obtainMultiplicationTriple();
        if (_benchmarkLevel == BenchmarkLevel::DETAILED) {
            end = System::currentTimeMillis();
            if (_isLogBenchmark) {
                Log::i(tag() + " Triple computation time: " + std::to_string(end - start) + " ms.");
            }
        }
    }

    // process
    process();
    if (_benchmarkLevel >= BenchmarkLevel::GENERAL) {
        end1 = System::currentTimeMillis();
        if (_benchmarkLevel == BenchmarkLevel::DETAILED && _isLogBenchmark) {
            Log::i(tag() + " MPI transmission and synchronization time: " + std::to_string(_mpiTime) + " ms.");
        }
        if (_isLogBenchmark) {
            Log::i(tag() + " Entire computation time: " + std::to_string(end1 - start) + " ms.");
        }
        _entireComputationTime = end1 - start;
    }
}

void AbstractMultiplicationShareExecutor::process() {
    bool bm = _benchmarkLevel == BenchmarkLevel::DETAILED;
    if (Mpi::isCalculator()) {
        /*
         * For member variables, x represents part of own secret,
         * which means that for party[0], x represents x in paper,
         * for party[1], that is y in paper.
         *
         * For all the variables in this project, subscript of a
         * variable represents the party who will use that to
         * compute. For example, x0 is used by executor itself
         * while x1 is used by the other one.
         * */
        int64_t x0, y0, *self, *other;
        self = Mpi::rank() == 0 ? &x0 : &y0;
        other = Mpi::rank() == 0 ? &y0 : &x0;
        *self = _x0;
        Mpi::exchange(&_x1, other, _mpiTime, bm);
        int64_t e0 = x0 - _a0;
        int64_t f0 = y0 - _b0;
        int64_t e1, f1;
        Mpi::exchange(&e0, &e1, _mpiTime, bm);
        Mpi::exchange(&f0, &f1, _mpiTime, bm);
        int64_t e = e0 + e1;
        int64_t f = f0 + f1;
        int64_t z0 = Mpi::rank() * e * f + f * _a0 + e * _b0 + _c0;

        if (Mpi::size() == 2) {
            int64_t z1;
            Mpi::exchange(&z0, &z1, _mpiTime, bm);
            _result = Math::ringMod(z0 + z1, _l);
        } else {
            Mpi::sendTo(&z0, Mpi::TASK_PUBLISHER_RANK, _mpiTime, bm);
        }
    } else {
        int64_t z0, z1;
        Mpi::recvFrom(&z0, 0, _mpiTime, bm);
        Mpi::recvFrom(&z1, 0, _mpiTime, bm);
        _result = Math::ringMod(z0 + z1, _l);
    }
}

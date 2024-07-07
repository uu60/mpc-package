//
// Created by 杜建璋 on 2024/7/7.
//

#include <iostream>
#include "executor/AbstractExecutor.h"
#include "mpi.h"

void AbstractExecutor::init(int argc, char **argv) {
    initMpcEnv(argc, argv);
    initData();
}

void AbstractExecutor::finalize() {
    // custom finalization
    customFinalize();
    // finalize mpi env
    MPI_Finalize();
}

void AbstractExecutor::initMpcEnv(int argc, char **argv) {
    // init MPI env
    MPI_Init(&argc, &argv);
    // process mpiRank and sum
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
    if (mpiSize != 2) {
        throw std::runtime_error("2 processes restricted.");
    }
}

//
// Created by 杜建璋 on 2024/7/7.
//

#include <iostream>
#include "executor/Executor.h"
#include "mpi.h"

// inited
bool Executor::envInited = false;
int Executor::mpiRank = 0;
int Executor::mpiSize = 0;

void Executor::finalizeMPI() {
    if (envInited) {
        MPI_Finalize();
        envInited = false;
    }
}

void Executor::initMPI(int argc, char **argv) {
    if (!envInited) {
        // init MPI env
        MPI_Init(&argc, &argv);
        // process mpiRank and sum
        MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
        MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
        if (mpiSize != 2) {
            throw std::runtime_error("2 processes restricted.");
        }
        envInited = true;
    }
}

void Executor::finalize() {
    // do nothing by default
}

int Executor::result() const {
    return res;
}

void Executor::exchange(int *send, int *recv) {
    MPI_Send(send, 1, MPI_INT, 1 - Executor::mpiRank, 0, MPI_COMM_WORLD);
    MPI_Recv(recv, 1, MPI_INT, 1 - Executor::mpiRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

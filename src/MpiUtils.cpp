//
// Created by 杜建璋 on 2024/7/15.
//

#include "utils/MpiUtils.h"
#include "mpi.h"
#include <iostream>

// inited
bool MpiUtils::envInited = false;
int MpiUtils::mpiRank = 0;
int MpiUtils::mpiSize = 0;

void MpiUtils::finalizeMPI() {
    if (envInited) {
        MPI_Finalize();
        envInited = false;
    }
}

void MpiUtils::initMPI(int argc, char **argv) {
    if (!envInited) {
        // inited MPI env
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

void MpiUtils::exchange(const int *send0, int *recv0) {
    send(send0);
    recv(recv0);
}

void MpiUtils::send(const int *send0) {
    MPI_Send(send0, 1, MPI_INT, 1 - mpiRank, 0, MPI_COMM_WORLD);
}

void MpiUtils::recv(int *recv0) {
    MPI_Recv(recv0, 1, MPI_INT, 1 - mpiRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

bool MpiUtils::isEnvInited() {
    return envInited;
}

int MpiUtils::getMpiSize() {
    return mpiSize;
}

int MpiUtils::getMpiRank() {
    return mpiRank;
}
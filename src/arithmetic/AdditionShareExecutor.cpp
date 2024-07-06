//
// Created by 杜建璋 on 2024/7/6.
//
#include <iostream>
#include "../../include/arithmetic/AdditionShareExecutor.h"
#include <mpi.h>
#include "../../include/utils/Utils.h"

void AdditionShareExecutor::init(int argc, char **argv) {
    // prepare mpi env
    initMpcEnv(argc, argv);
    // get holding param
    obtainX();
    // get saved
    generateSaved();
}

void AdditionShareExecutor::generateSaved() {
    // return random by default
    x1 = Utils::generateRandomInt();
    x2 = x - x1;
}

void AdditionShareExecutor::exchangePart() {
    Utils::exchangeData(&x2, &y2, mpiRank);
}

void AdditionShareExecutor::initMpcEnv(int argc, char **argv) {
    // init MPI env
    MPI_Init(&argc, &argv);
    // process mpiRank and sum
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
    if (mpiSize != 2) {
        throw std::runtime_error("2 processes restricted.");
    }
}

void AdditionShareExecutor::exchangeTemp() {
    Utils::exchangeData(&temp, &recvTemp, mpiRank);
}

void AdditionShareExecutor::calculateTemp() {
    temp = x1 + y2;
}

int AdditionShareExecutor::result() const {
    return temp + recvTemp;
}


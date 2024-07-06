//
// Created by 杜建璋 on 2024/7/6.
//

#include "../../include/utils/Utils.h"
#include "random"
#include "mpi.h"

int Utils::generateRandomInt() {
    // random engine
    std::random_device rd;
    std::mt19937 generator(rd());

    // distribution in integer range
    std::uniform_int_distribution<int> distribution(-RAND_MAX - 1, RAND_MAX);

    // generation
    return distribution(generator);
}

void Utils::exchangeData(int *px2, int *py2, int mpiRank) {
    MPI_Send(px2, 1, MPI_INT, 1 - mpiRank, 0, MPI_COMM_WORLD);
    MPI_Recv(py2, 1, MPI_INT, 1 - mpiRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

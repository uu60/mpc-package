//
// Created by 杜建璋 on 2024/7/15.
//

#include "utils/MpiUtils.h"
#include "utils/MathUtils.h"
#include <mpi.h>
#include <iostream>
#include <limits>
#include <vector>
#include "utils/Log.h"
#include "utils/System.h"

// init
bool MpiUtils::_envInited = false;
int MpiUtils::_mpiRank = 0;
int MpiUtils::_mpiSize = 0;

void MpiUtils::finalizeMPI() {
    if (_envInited) {
        MPI_Finalize();
        _envInited = false;
    }
}

void MpiUtils::initMPI(int argc, char **argv) {
    if (!_envInited) {
        // init MPI env
        MPI_Init(&argc, &argv);
        // process _mpiRank and sum
        MPI_Comm_rank(MPI_COMM_WORLD, &_mpiRank);
        MPI_Comm_size(MPI_COMM_WORLD, &_mpiSize);
        if (_mpiSize != 2) {
            throw std::runtime_error("2 processes restricted.");
        }
        _envInited = true;
    }
}

void MpiUtils::exchange(const int64_t *data, int64_t *target) {
    send(data);
    recv(target);
}

void MpiUtils::send(const int64_t *data) {
    MPI_Send(data, 1, MPI_INT64_T, 1 - _mpiRank, 0, MPI_COMM_WORLD);
}

void MpiUtils::send(const std::string *data) {
    if (data->length() > static_cast<size_t>(std::numeric_limits<int>::max())) {
        std::cerr << "String size exceeds MPI_Send limit." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Send(data->data(), static_cast<int>(data->length()), MPI_CHAR, 1 - _mpiRank, 0, MPI_COMM_WORLD);
//    Log::d("send:  " + *data);
}

void MpiUtils::recv(int64_t *target) {
    MPI_Recv(target, 1, MPI_INT64_T, 1 - _mpiRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void MpiUtils::recv(std::string *target) {
    MPI_Status status;
    MPI_Probe(1 - _mpiRank, 0, MPI_COMM_WORLD, &status);

    int count;
    MPI_Get_count(&status, MPI_CHAR, &count);

    std::vector<char> buffer(count);
    MPI_Recv( buffer.data(), count, MPI_CHAR, 1 - _mpiRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    *target = std::string(buffer.data(), count);
//    Log::d("recv: " + *target);
}

bool MpiUtils::isEnvInited() {
    return _envInited;
}

int MpiUtils::getMpiSize() {
    return _mpiSize;
}

int MpiUtils::getMpiRank() {
    return _mpiRank;
}

void MpiUtils::exchange(const int64_t *data, int64_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    exchange(data, target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void MpiUtils::send(const int64_t *data, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(data);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void MpiUtils::recv(int64_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void MpiUtils::send(const std::string *data, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(data);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void MpiUtils::recv(std::string *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

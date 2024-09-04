//
// Created by 杜建璋 on 2024/7/15.
//

#include "utils/Mpi.h"
#include <mpi.h>
#include <iostream>
#include <limits>
#include <vector>
#include "utils/Log.h"
#include "utils/System.h"

// init
const int Mpi::TASK_PUBLISHER_RANK = 2;
bool Mpi::_envInited = false;
int Mpi::_mpiRank = 0;
int Mpi::_mpiSize = 0;

void Mpi::finalize() {
    if (_envInited) {
        MPI_Finalize();
        _envInited = false;
    }
}

void Mpi::init(int argc, char **argv) {
    if (!_envInited) {
        // init MPI env
        MPI_Init(&argc, &argv);
        // process _mpiRank and sum
        MPI_Comm_rank(MPI_COMM_WORLD, &_mpiRank);
        MPI_Comm_size(MPI_COMM_WORLD, &_mpiSize);
        if (_mpiSize != 3) {
            throw std::runtime_error("3 processes restricted.");
        }
        _envInited = true;
    }
}

void Mpi::exchange(const int64_t *data, int64_t *target) {
    send(data);
    recv(target);
}

void Mpi::send(const int64_t *data) {
    MPI_Send(data, 1, MPI_INT64_T, 1 - _mpiRank, 0, MPI_COMM_WORLD);
}

void Mpi::send(const std::string *data) {
    if (data->length() > static_cast<size_t>(std::numeric_limits<int>::max())) {
        std::cerr << "String size exceeds MPI_Send limit." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Send(data->data(), static_cast<int>(data->length()), MPI_CHAR, 1 - _mpiRank, 0, MPI_COMM_WORLD);
//    Log::d("send:  " + *data);
}

void Mpi::recv(int64_t *target) {
    MPI_Recv(target, 1, MPI_INT64_T, 1 - _mpiRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Mpi::recv(std::string *target) {
    MPI_Status status;
    MPI_Probe(1 - _mpiRank, 0, MPI_COMM_WORLD, &status);

    int count;
    MPI_Get_count(&status, MPI_CHAR, &count);

    std::vector<char> buffer(count);
    MPI_Recv( buffer.data(), count, MPI_CHAR, 1 - _mpiRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    *target = std::string(buffer.data(), count);
//    Log::d("recv: " + *target);
}

bool Mpi::inited() {
    return _envInited;
}

int Mpi::size() {
    return _mpiSize;
}

int Mpi::rank() {
    return _mpiRank;
}

void Mpi::exchange(const int64_t *data, int64_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    exchange(data, target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::send(const int64_t *data, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(data);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv(int64_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::send(const std::string *data, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(data);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv(std::string *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::send2(const int64_t *data) {
    MPI_Send(data, 1, MPI_INT64_T, TASK_PUBLISHER_RANK, 0, MPI_COMM_WORLD);
}

void Mpi::send2(const int64_t *data, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send2(data);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::send2(const std::string *data) {
    if (data->length() > static_cast<size_t>(std::numeric_limits<int>::max())) {
        std::cerr << "String size exceeds MPI_Send limit." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Send(data->data(), static_cast<int>(data->length()), MPI_CHAR, TASK_PUBLISHER_RANK, 0, MPI_COMM_WORLD);
}

void Mpi::send2(const std::string *data, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send2(data);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv2(int64_t *target, int senderRank) {
    MPI_Recv(target, 1, MPI_INT64_T, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Mpi::recv2(int64_t *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv2(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv2(std::string *target, int senderRank) {
    MPI_Status status;
    MPI_Probe(senderRank, 0, MPI_COMM_WORLD, &status);

    int count;
    MPI_Get_count(&status, MPI_CHAR, &count);

    std::vector<char> buffer(count);
    MPI_Recv( buffer.data(), count, MPI_CHAR, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    *target = std::string(buffer.data(), count);
}

void Mpi::recv2(std::string *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv2(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}





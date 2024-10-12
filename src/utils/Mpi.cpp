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
const int Mpi::CLIENT_RANK = 2;
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
            throw std::runtime_error("3 parties restricted.");
        }
        _envInited = true;
    }
}

void Mpi::sexch(const int64_t *source, int64_t *target) {
    ssend(source);
    srecv(target);
}

void Mpi::ssend(const int64_t *source) {
    send(source, 1 - _mpiRank);
}

void Mpi::ssend(const std::string *source) {
    send(source, 1 - _mpiRank);
}

void Mpi::srecv(int64_t *target) {
    recv(target, 1 - _mpiRank);
}

void Mpi::srecv(std::string *target) {
    recv(target, 1 - _mpiRank);
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

void Mpi::sexch(const int64_t *source, int64_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    sexch(source, target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::ssend(const int64_t *source, int64_t &mpiTime) {
    send(source, 1 - _mpiRank, mpiTime);
}

void Mpi::srecv(int64_t *target, int64_t &mpiTime) {
    recv(target, 1 - _mpiRank, mpiTime);
}

void Mpi::ssend(const std::string *source, int64_t &mpiTime) {
    send(source, 1 - _mpiRank, mpiTime);
}

void Mpi::srecv(std::string *target, int64_t &mpiTime) {
    recv(target, 1 - _mpiRank, mpiTime);
}

void Mpi::send(const int64_t *source, int receiverRank) {
    MPI_Send(source, 1, MPI_INT64_T, receiverRank, 0, MPI_COMM_WORLD);
}

void Mpi::send(const int64_t *source, int receiverRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(source, receiverRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::send(const std::string *source, int receiverRank) {
    if (source->length() > static_cast<size_t>(std::numeric_limits<int>::max())) {
        std::cerr << "String size exceeds MPI_Send limit." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Send(source->data(), static_cast<int>(source->length()), MPI_CHAR, receiverRank, 0, MPI_COMM_WORLD);
}

void Mpi::send(const std::string *source, int receiverRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(source, receiverRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv(int64_t *target, int senderRank) {
    MPI_Recv(target, 1, MPI_INT64_T, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Mpi::recv(int64_t *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv(std::string *target, int senderRank) {
    MPI_Status status;
    MPI_Probe(senderRank, 0, MPI_COMM_WORLD, &status);

    int count;
    MPI_Get_count(&status, MPI_CHAR, &count);

    std::vector<char> buffer(count);
    MPI_Recv( buffer.data(), count, MPI_CHAR, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    *target = std::string(buffer.data(), count);
}

void Mpi::recv(std::string *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

bool Mpi::isServer() {
    return _mpiRank != CLIENT_RANK;
}

bool Mpi::isClient() {
    return !isServer();
}

void Mpi::send(const bool *source, int receiverRank) {
    MPI_Send(source, 1, MPI_CXX_BOOL, receiverRank, 0, MPI_COMM_WORLD);
}

void Mpi::send(const bool *source, int receiverRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(source, receiverRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv(bool *target, int senderRank) {
    MPI_Recv(target, 1, MPI_CXX_BOOL, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Mpi::recv(bool *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::sexch(const bool *source, bool *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    sexch(source, target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::ssend(const bool *source) {
    send(source, 1 - _mpiRank);
}

void Mpi::ssend(const bool *source, int64_t &mpiTime) {
    send(source, 1 - _mpiRank, mpiTime);
}

void Mpi::srecv(bool *target) {
    recv(target, 1 - _mpiRank);
}

void Mpi::srecv(bool *target, int64_t &mpiTime) {
    recv(target, 1 - _mpiRank, mpiTime);
}

void Mpi::sexch(const bool *source, bool *target) {
    ssend(source);
    srecv(target);
}

// exchange source (for rank of 0 and 1)
void Mpi::sexch(const int64_t *source, int64_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sexch(source, target, mpiTime);
    } else {
        sexch(source, target);
    }
}

void Mpi::sexch(const bool *source, bool *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sexch(source, target, mpiTime);
    } else {
        sexch(source, target);
    }
}

// ssend
void Mpi::ssend(const int64_t *source, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        ssend(source, mpiTime);
    } else {
        ssend(source);
    }
}

void Mpi::ssend(const bool *source, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        ssend(source, mpiTime);
    } else {
        ssend(source);
    }
}

void Mpi::ssend(const std::string *source, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        ssend(source, mpiTime);
    } else {
        ssend(source);
    }
}

// srecv
void Mpi::srecv(int64_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        srecv(target, mpiTime);
    } else {
        srecv(target);
    }
}

void Mpi::srecv(bool *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        srecv(target, mpiTime);
    } else {
        srecv(target);
    }
}

void Mpi::srecv(std::string *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        srecv(target, mpiTime);
    } else {
        srecv(target);
    }
}

// reconstruct (for transmission between <0 and 2> or <1 and 2>)
void Mpi::send(const int64_t *source, int receiverRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        send(source, receiverRank, mpiTime);
    } else {
        send(source, receiverRank);
    }
}

void Mpi::send(const bool *source, int receiverRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        send(source, receiverRank, mpiTime);
    } else {
        send(source, receiverRank);
    }
}

void Mpi::send(const std::string *source, int receiverRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        send(source, receiverRank, mpiTime);
    } else {
        send(source, receiverRank);
    }
}

void Mpi::recv(int64_t *target, int senderRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recv(target, senderRank, mpiTime);
    } else {
        recv(target, senderRank);
    }
}

void Mpi::recv(bool *target, int senderRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recv(target, senderRank, mpiTime);
    } else {
        recv(target, senderRank);
    }
}

void Mpi::recv(std::string *target, int senderRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recv(target, senderRank, mpiTime);
    } else {
        recv(target, senderRank);
    }
}

// sexch functions
void Mpi::sexch(const int8_t *source, int8_t *target) {
    ssend(source);
    srecv(target);
}

void Mpi::sexch(const int8_t *source, int8_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    sexch(source, target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::sexch(const int8_t *source, int8_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sexch(source, target, mpiTime);
    } else {
        sexch(source, target);
    }
}

// ssend functions
void Mpi::ssend(const int8_t *source) {
    send(source, 1 - _mpiRank);
}

void Mpi::ssend(const int8_t *source, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    ssend(source);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::ssend(const int8_t *source, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        ssend(source, mpiTime);
    } else {
        ssend(source);
    }
}

// srecv functions
void Mpi::srecv(int8_t *target) {
    recv(target, 1 - _mpiRank);
}

void Mpi::srecv(int8_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    srecv(target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::srecv(int8_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        srecv(target, mpiTime);
    } else {
        srecv(target);
    }
}

// send functions
void Mpi::send(const int8_t *source, int receiverRank) {
    MPI_Send(source, 1, MPI_INT8_T, receiverRank, 0, MPI_COMM_WORLD);
}

void Mpi::send(const int8_t *source, int receiverRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(source, receiverRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::send(const int8_t *source, int receiverRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        send(source, receiverRank, mpiTime);
    } else {
        send(source, receiverRank);
    }
}

// recv functions
void Mpi::recv(int8_t *target, int senderRank) {
    MPI_Recv(target, 1, MPI_INT8_T, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Mpi::recv(int8_t *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv(int8_t *target, int senderRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recv(target, senderRank, mpiTime);
    } else {
        recv(target, senderRank);
    }
}

// sexch functions
void Mpi::sexch(const int16_t *source, int16_t *target) {
    ssend(source);
    srecv(target);
}

void Mpi::sexch(const int16_t *source, int16_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    sexch(source, target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::sexch(const int16_t *source, int16_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sexch(source, target, mpiTime);
    } else {
        sexch(source, target);
    }
}

// ssend functions
void Mpi::ssend(const int16_t *source) {
    send(source, 1 - _mpiRank);
}

void Mpi::ssend(const int16_t *source, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    ssend(source);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::ssend(const int16_t *source, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        ssend(source, mpiTime);
    } else {
        ssend(source);
    }
}

// srecv functions
void Mpi::srecv(int16_t *target) {
    recv(target, 1 - _mpiRank);
}

void Mpi::srecv(int16_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    srecv(target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::srecv(int16_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        srecv(target, mpiTime);
    } else {
        srecv(target);
    }
}

// send functions
void Mpi::send(const int16_t *source, int receiverRank) {
    MPI_Send(source, 1, MPI_INT16_T, receiverRank, 0, MPI_COMM_WORLD);
}

void Mpi::send(const int16_t *source, int receiverRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(source, receiverRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::send(const int16_t *source, int receiverRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        send(source, receiverRank, mpiTime);
    } else {
        send(source, receiverRank);
    }
}

// recv functions
void Mpi::recv(int16_t *target, int senderRank) {
    MPI_Recv(target, 1, MPI_INT16_T, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Mpi::recv(int16_t *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv(int16_t *target, int senderRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recv(target, senderRank, mpiTime);
    } else {
        recv(target, senderRank);
    }
}

// sexch functions
void Mpi::sexch(const int32_t *source, int32_t *target) {
    ssend(source);
    srecv(target);
}

void Mpi::sexch(const int32_t *source, int32_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    sexch(source, target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::sexch(const int32_t *source, int32_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sexch(source, target, mpiTime);
    } else {
        sexch(source, target);
    }
}

// ssend functions
void Mpi::ssend(const int32_t *source) {
    send(source, 1 - _mpiRank);
}

void Mpi::ssend(const int32_t *source, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    ssend(source);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::ssend(const int32_t *source, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        ssend(source, mpiTime);
    } else {
        ssend(source);
    }
}

// srecv functions
void Mpi::srecv(int32_t *target) {
    recv(target, 1 - _mpiRank);
}

void Mpi::srecv(int32_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    srecv(target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::srecv(int32_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        srecv(target, mpiTime);
    } else {
        srecv(target);
    }
}

// send functions
void Mpi::send(const int32_t *source, int receiverRank) {
    MPI_Send(source, 1, MPI_INT32_T, receiverRank, 0, MPI_COMM_WORLD);
}

void Mpi::send(const int32_t *source, int receiverRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    send(source, receiverRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::send(const int32_t *source, int receiverRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        send(source, receiverRank, mpiTime);
    } else {
        send(source, receiverRank);
    }
}

// recv functions
void Mpi::recv(int32_t *target, int senderRank) {
    MPI_Recv(target, 1, MPI_INT32_T, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Mpi::recv(int32_t *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recv(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recv(int32_t *target, int senderRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recv(target, senderRank, mpiTime);
    } else {
        recv(target, senderRank);
    }
}
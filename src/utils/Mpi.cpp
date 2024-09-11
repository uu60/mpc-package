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
const int Mpi::DATA_HOLDER_RANK = 2;
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

void Mpi::exchangeC(const int64_t *source, int64_t *target) {
    sendC(source);
    recvC(target);
}

void Mpi::sendC(const int64_t *source) {
    sendTo(source, 1 - _mpiRank);
}

void Mpi::sendC(const std::string *source) {
    sendTo(source, 1 - _mpiRank);
}

void Mpi::recvC(int64_t *target) {
    recvFrom(target, 1 - _mpiRank);
}

void Mpi::recvC(std::string *target) {
    recvFrom(target, 1 - _mpiRank);
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

void Mpi::exchangeC(const int64_t *source, int64_t *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    exchangeC(source, target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::sendC(const int64_t *source, int64_t &mpiTime) {
    sendTo(source, 1 - _mpiRank, mpiTime);
}

void Mpi::recvC(int64_t *target, int64_t &mpiTime) {
    recvFrom(target, 1 - _mpiRank, mpiTime);
}

void Mpi::sendC(const std::string *source, int64_t &mpiTime) {
    sendTo(source, 1 - _mpiRank, mpiTime);
}

void Mpi::recvC(std::string *target, int64_t &mpiTime) {
    recvFrom(target, 1 - _mpiRank, mpiTime);
}

void Mpi::sendTo(const int64_t *source, int receiverRank) {
    MPI_Send(source, 1, MPI_INT64_T, receiverRank, 0, MPI_COMM_WORLD);
}

void Mpi::sendTo(const int64_t *source, int receiverRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    sendTo(source, receiverRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::sendTo(const std::string *source, int receiverRank) {
    if (source->length() > static_cast<size_t>(std::numeric_limits<int>::max())) {
        std::cerr << "String size exceeds MPI_Send limit." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Send(source->data(), static_cast<int>(source->length()), MPI_CHAR, receiverRank, 0, MPI_COMM_WORLD);
}

void Mpi::sendTo(const std::string *source, int receiverRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    sendTo(source, receiverRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recvFrom(int64_t *target, int senderRank) {
    MPI_Recv(target, 1, MPI_INT64_T, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Mpi::recvFrom(int64_t *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recvFrom(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recvFrom(std::string *target, int senderRank) {
    MPI_Status status;
    MPI_Probe(senderRank, 0, MPI_COMM_WORLD, &status);

    int count;
    MPI_Get_count(&status, MPI_CHAR, &count);

    std::vector<char> buffer(count);
    MPI_Recv( buffer.data(), count, MPI_CHAR, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    *target = std::string(buffer.data(), count);
}

void Mpi::recvFrom(std::string *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recvFrom(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

bool Mpi::isCalculator() {
    return _mpiRank != DATA_HOLDER_RANK;
}

bool Mpi::isDataHolder() {
    return !isCalculator();
}

void Mpi::sendTo(const bool *source, int receiverRank) {
    MPI_Send(source, 1, MPI_CXX_BOOL, receiverRank, 0, MPI_COMM_WORLD);
}

void Mpi::sendTo(const bool *source, int receiverRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    sendTo(source, receiverRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::recvFrom(bool *target, int senderRank) {
    MPI_Recv(target, 1, MPI_CXX_BOOL, senderRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Mpi::recvFrom(bool *target, int senderRank, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    recvFrom(target, senderRank);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::exchangeC(const bool *source, bool *target, int64_t &mpiTime) {
    int64_t start = System::currentTimeMillis();
    exchangeC(source, target);
    int64_t end = System::currentTimeMillis();
    mpiTime += end - start;
}

void Mpi::sendC(const bool *source) {
    sendTo(source, 1 - _mpiRank);
}

void Mpi::sendC(const bool *source, int64_t &mpiTime) {
    sendTo(source, 1 - _mpiRank, mpiTime);
}

void Mpi::recvC(bool *target) {
    recvFrom(target, 1 - _mpiRank);
}

void Mpi::recvC(bool *target, int64_t &mpiTime) {
    recvFrom(target, 1 - _mpiRank, mpiTime);
}

void Mpi::exchangeC(const bool *source, bool *target) {
    sendC(source);
    recvC(target);
}

// exchange source (for rank of 0 and 1)
void Mpi::exchangeC(const int64_t *source, int64_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        exchangeC(source, target, mpiTime);
    } else {
        exchangeC(source, target);
    }
}

void Mpi::exchangeC(const bool *source, bool *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        exchangeC(source, target, mpiTime);
    } else {
        exchangeC(source, target);
    }
}

// sendC
void Mpi::sendC(const int64_t *source, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sendC(source, mpiTime);
    } else {
        sendC(source);
    }
}

void Mpi::sendC(const bool *source, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sendC(source, mpiTime);
    } else {
        sendC(source);
    }
}

void Mpi::sendC(const std::string *source, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sendC(source, mpiTime);
    } else {
        sendC(source);
    }
}

// recvC
void Mpi::recvC(int64_t *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recvC(target, mpiTime);
    } else {
        recvC(target);
    }
}

void Mpi::recvC(bool *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recvC(target, mpiTime);
    } else {
        recvC(target);
    }
}

void Mpi::recvC(std::string *target, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recvC(target, mpiTime);
    } else {
        recvC(target);
    }
}

// reconstruct (for transmission between <0 and 2> or <1 and 2>)
void Mpi::sendTo(const int64_t *source, int receiverRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sendTo(source, receiverRank, mpiTime);
    } else {
        sendTo(source, receiverRank);
    }
}

void Mpi::sendTo(const bool *source, int receiverRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sendTo(source, receiverRank, mpiTime);
    } else {
        sendTo(source, receiverRank);
    }
}

void Mpi::sendTo(const std::string *source, int receiverRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        sendTo(source, receiverRank, mpiTime);
    } else {
        sendTo(source, receiverRank);
    }
}

void Mpi::recvFrom(int64_t *target, int senderRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recvFrom(target, senderRank, mpiTime);
    } else {
        recvFrom(target, senderRank);
    }
}

void Mpi::recvFrom(bool *target, int senderRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recvFrom(target, senderRank, mpiTime);
    } else {
        recvFrom(target, senderRank);
    }
}

void Mpi::recvFrom(std::string *target, int senderRank, int64_t &mpiTime, bool calculateTime) {
    if (calculateTime) {
        recvFrom(target, senderRank, mpiTime);
    } else {
        recvFrom(target, senderRank);
    }
}
//
// Created by 杜建璋 on 2024/7/15.
//

#ifndef MPC_PACKAGE_MPI_H
#define MPC_PACKAGE_MPI_H
#include <string>

/**
 * For sender, mpi rank must be 0 or 1.
 * The task publisher must be rank of 2.
 * Attention: Currently, there is no restriction in this util class.
 */
class Mpi {
public:
    static const int DATA_HOLDER_RANK;
private:
    // mpi env init
    static bool _envInited;
    // joined party number
    static int _mpiSize;
    // _mpiRank of current device
    static int _mpiRank;
public:
    static bool inited();
    static int size();
    static int rank();
    // init env
    static void init(int argc, char **argv);
    static void finalize();
    // judge identity
    static bool isCalculator();
    static bool isDataHolder();
// exchange source (for rank of 0 and 1)
    static void exchangeC(const int64_t *source, int64_t *target);
    static void exchangeC(const int64_t *source, int64_t *target, int64_t &mpiTime);
    static void exchangeC(const int64_t *source, int64_t *target, int64_t &mpiTime, bool calculateTime);
    static void exchangeC(const bool *source, bool *target);
    static void exchangeC(const bool *source, bool *target, int64_t &mpiTime);
    static void exchangeC(const bool *source, bool *target, int64_t &mpiTime, bool calculateTime);

// sendC
    static void sendC(const int64_t *source);
    static void sendC(const int64_t *source, int64_t &mpiTime);
    static void sendC(const int64_t *source, int64_t &mpiTime, bool calculateTime);
    static void sendC(const bool *source);
    static void sendC(const bool *source, int64_t &mpiTime);
    static void sendC(const bool *source, int64_t &mpiTime, bool calculateTime);
    static void sendC(const std::string *source);
    static void sendC(const std::string *source, int64_t &mpiTime);
    static void sendC(const std::string *source, int64_t &mpiTime, bool calculateTime);

// recvC
    static void recvC(int64_t *target);
    static void recvC(int64_t *target, int64_t &mpiTime);
    static void recvC(int64_t *target, int64_t &mpiTime, bool calculateTime);
    static void recvC(bool *target);
    static void recvC(bool *target, int64_t &mpiTime);
    static void recvC(bool *target, int64_t &mpiTime, bool calculateTime);
    static void recvC(std::string *target);
    static void recvC(std::string *target, int64_t &mpiTime);
    static void recvC(std::string *target, int64_t &mpiTime, bool calculateTime);

// reconstruct (for transmission between <0 and 2> or <1 and 2>)
    static void sendTo(const int64_t *source, int receiverRank);
    static void sendTo(const int64_t *source, int receiverRank, int64_t &mpiTime);
    static void sendTo(const int64_t *source, int receiverRank, int64_t &mpiTime, bool calculateTime);
    static void sendTo(const bool *source, int receiverRank);
    static void sendTo(const bool *source, int receiverRank, int64_t &mpiTime);
    static void sendTo(const bool *source, int receiverRank, int64_t &mpiTime, bool calculateTime);
    static void sendTo(const std::string *source, int receiverRank);
    static void sendTo(const std::string *source, int receiverRank, int64_t &mpiTime);
    static void sendTo(const std::string *source, int receiverRank, int64_t &mpiTime, bool calculateTime);
    static void recvFrom(int64_t *target, int senderRank);
    static void recvFrom(int64_t *target, int senderRank, int64_t &mpiTime);
    static void recvFrom(int64_t *target, int senderRank, int64_t &mpiTime, bool calculateTime);
    static void recvFrom(bool *target, int senderRank);
    static void recvFrom(bool *target, int senderRank, int64_t &mpiTime);
    static void recvFrom(bool *target, int senderRank, int64_t &mpiTime, bool calculateTime);
    static void recvFrom(std::string *target, int senderRank);
    static void recvFrom(std::string *target, int senderRank, int64_t &mpiTime);
    static void recvFrom(std::string *target, int senderRank, int64_t &mpiTime, bool calculateTime);
};


#endif //MPC_PACKAGE_MPI_H

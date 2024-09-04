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
private:
    static const int TASK_PUBLISHER_RANK;
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
    // exchange data (for rank of 0 and 1)
    static void exchange(const int64_t *data, int64_t *target);
    static void exchange(const int64_t *data, int64_t *target, int64_t &mpiTime);
    static void send(const int64_t *data);
    static void send(const int64_t *data, int64_t &mpiTime);
    static void send(const std::string *data);
    static void send(const std::string *data, int64_t &mpiTime);
    static void recv(int64_t *target);
    static void recv(int64_t *target, int64_t &mpiTime);
    static void recv(std::string *target);
    static void recv(std::string *target, int64_t &mpiTime);
    // reconstruct (for transmission between <0 and 2> or <1 and 2>)
    static void send2(const int64_t *data);
    static void send2(const int64_t *data, int64_t &mpiTime);
    static void send2(const std::string *data);
    static void send2(const std::string *data, int64_t &mpiTime);
    static void recv2(int64_t *target, int senderRank);
    static void recv2(int64_t *target, int senderRank, int64_t &mpiTime);
    static void recv2(std::string *target, int senderRank);
    static void recv2(std::string *target, int senderRank, int64_t &mpiTime);
};


#endif //MPC_PACKAGE_MPI_H

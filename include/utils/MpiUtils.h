//
// Created by 杜建璋 on 2024/7/15.
//

#ifndef MPC_PACKAGE_MPIUTILS_H
#define MPC_PACKAGE_MPIUTILS_H
#include <string>

class MpiUtils {
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
    // exchange data
    static void exchange(const int64_t *data, int64_t *target);
    static void exchange(const int64_t *data, int64_t *target, int64_t &mpiTime);
    static void send(const int64_t *data);
    static void send(const int64_t *data, int64_t &mpiTime);
    static void recv(int64_t *target);
    static void recv(int64_t *target, int64_t &mpiTime);
    static void send(const std::string *data);
    static void send(const std::string *data, int64_t &mpiTime);
    static void recv(std::string *target);
    static void recv(std::string *target, int64_t &mpiTime);
};


#endif //MPC_PACKAGE_MPIUTILS_H

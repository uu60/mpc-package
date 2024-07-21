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
    static bool isEnvInited();
    static int getMpiSize();
    static int getMpiRank();
    // init env
    static void initMPI(int argc, char **argv);
    static void finalizeMPI();
    // exchange data
    static void exchange(const int64_t *data, int64_t *target);
    static void send(const int64_t *data);
    static void recv(int64_t *target);
    static void send(const std::string *encoded);
    static void recv(std::string *target);
};


#endif //MPC_PACKAGE_MPIUTILS_H

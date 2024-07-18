//
// Created by 杜建璋 on 2024/7/15.
//

#ifndef MPC_PACKAGE_MPIUTILS_H
#define MPC_PACKAGE_MPIUTILS_H

class MpiUtils {
private:
    // mpi env inited
    static bool envInited;
    // joined party number
    static int mpiSize;
    // mpiRank of current device
    static int mpiRank;
public:
    static bool isEnvInited();
    static int getMpiSize();
    static int getMpiRank();
    // inited env
    static void initMPI(int argc, char **argv);
    static void finalizeMPI();
    // exchange data
    static void exchange(const int *send, int *recv);
    static void send(const int *send);
    static void recv(int *recv);
};


#endif //MPC_PACKAGE_MPIUTILS_H

//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_EXECUTOR_H
#define MPC_PACKAGE_EXECUTOR_H

class Executor {
protected:
    // mpi env inited
    static bool envInited;
    // joined party number
    static int mpiSize;
    // mpiRank of current device
    static int mpiRank;
    // result
    int res{};
public:
    // init env
    static void initMPI(int argc, char **argv);
    static void finalizeMPI();
    // secret sharing process
    virtual void compute() = 0;
    // get calculated result
    int result() const;
protected:
    // modify this to prepare data after env
    virtual void init() = 0;
    // before env finalized
    virtual void finalize();
};

#endif //MPC_PACKAGE_EXECUTOR_H

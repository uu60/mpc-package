//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_ABSTRACTEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTEXECUTOR_H
#include <vector>

class AbstractExecutor {
protected:
    // joined party number
    int mpiSize{};
    // mpiRank of current device
    int mpiRank{};
    // result
    std::vector<int> res;
public:
    // whole init process, containing env and data
    // should not override
    void init(int argc, char **argv);
    // secret sharing process
    virtual void compute() = 0;
    // get calculated result
    std::vector<int> result();
    void finalize();
protected:
    // modify this to prepare data after env
    virtual void generateShare() = 0;
    virtual void customFinalize();
private:
    void initMpcEnv(int argc, char **argv);
};


#endif //MPC_PACKAGE_ABSTRACTEXECUTOR_H

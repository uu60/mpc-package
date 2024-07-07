//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_ABSTRACTEXECUTOR_H
#define MPC_PACKAGE_ABSTRACTEXECUTOR_H


class AbstractExecutor {
protected:
    // joined party number
    int mpiSize{};
    // mpiRank of current device
    int mpiRank{};
public:
    // whole init process, containing env and data
    // should not override
    void init(int argc, char **argv);
protected:
    // modify this to prepare data after env
    virtual void initData() = 0;
    virtual void calculate() = 0;
    virtual int result() = 0;
    virtual void customFinalize();
    void finalize();
private:
    void initMpcEnv(int argc, char **argv);
};


#endif //MPC_PACKAGE_ABSTRACTEXECUTOR_H

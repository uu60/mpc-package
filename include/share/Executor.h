//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_EXECUTOR_H
#define MPC_PACKAGE_EXECUTOR_H

class Executor {
protected:
    // result
    int res{};
public:
    // secret sharing process
    virtual void compute() = 0;
    // get calculated result
    int result() const;
protected:
    // custom inited
    virtual void inited();
    virtual void finalize();
};

#endif //MPC_PACKAGE_EXECUTOR_H

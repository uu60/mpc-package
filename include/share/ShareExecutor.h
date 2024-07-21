//
// Created by 杜建璋 on 2024/7/7.
//

#ifndef MPC_PACKAGE_SHAREEXECUTOR_H
#define MPC_PACKAGE_SHAREEXECUTOR_H

#include <cstdint>

class ShareExecutor {
protected:
    // result
    int64_t _res{};
public:
    // secret sharing process
    virtual void compute() = 0;
    // get calculated result
    int64_t result() const;
protected:
    virtual void finalize();
};

#endif //MPC_PACKAGE_SHAREEXECUTOR_H

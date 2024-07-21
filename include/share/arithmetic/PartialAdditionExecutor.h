//
// Created by 杜建璋 on 2024/7/12.
//

#ifndef MPC_PACKAGE_PARTIALADDITIONEXECUTOR_H
#define MPC_PACKAGE_PARTIALADDITIONEXECUTOR_H

#include "share/Executor.h"

class PartialAdditionExecutor : public Executor {
protected:
    /*
     * Alice holds _xa and _ya
     * Bob holds _xb and yb
     * compute _x + y => _za + _zb = (_xa + _ya) + (_xb + yb)
     */

    // part of _x
    int64_t _xa{};
    // part of y
    int64_t _ya{};
    int64_t _za{};
    int64_t _zb{};

public:
    void init(int64_t xa, int64_t ya);

    // compute process
    void compute() override;
};


#endif //MPC_PACKAGE_PARTIALADDITIONEXECUTOR_H

//
// Created by 杜建璋 on 2024/7/13.
//

#ifndef MPC_PACKAGE_COMPLETEADDITIONSHAREEXECUTOR_H
#define MPC_PACKAGE_COMPLETEADDITIONSHAREEXECUTOR_H

#include "share/ShareExecutor.h"

class CompleteAdditionShareExecutor : public ShareExecutor {
protected:
    /*
     * Alice holds _x = _xa + _xb
     * Bob holds y = _ya + yb
     * compute _x + y => _za + _zb = (_xa + _ya) + (yb + _xb)
     */
    int64_t _x{};
    int64_t _xa{};
    int64_t _xb{};
    int64_t _ya{};
    int64_t _za{};
    int64_t _zb{};
public:
    explicit CompleteAdditionShareExecutor(int64_t x);
    void compute() override;
};


#endif //MPC_PACKAGE_COMPLETEADDITIONSHAREEXECUTOR_H

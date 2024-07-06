//
// Created by 杜建璋 on 2024/7/6.
//

#ifndef MPC_PACKAGE_UTILS_H
#define MPC_PACKAGE_UTILS_H


class Utils {
public:
    // generate a random
    static int generateRandomInt();
    // exchange data
    static void exchangeData(int *px2, int *py2, int mpiRank);
};


#endif //MPC_PACKAGE_UTILS_H

//
// Created by 杜建璋 on 2024/7/6.
//

#ifndef MPC_PACKAGE_MATHUTILS_H
#define MPC_PACKAGE_MATHUTILS_H


class MathUtils {
public:
    // generate a random
    static int randomInt();
    static int randomInt(int lowest, int highest);

    // pow for int
    static int pow(int base, int exponent);
};


#endif //MPC_PACKAGE_MATHUTILS_H

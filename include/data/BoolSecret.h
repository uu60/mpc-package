//
// Created by 杜建璋 on 2024/9/13.
//

#ifndef MPC_PACKAGE_BOOLSECRET_H
#define MPC_PACKAGE_BOOLSECRET_H
#include "./Secret.h"

class BoolSecret : public Secret {
private:
    bool _data{};
public:
    explicit BoolSecret(bool x);

    [[nodiscard]] BoolSecret share() const;
    [[nodiscard]] BoolSecret xor_(bool yi) const;
    [[nodiscard]] BoolSecret xor_(BoolSecret yi) const;
    [[nodiscard]] BoolSecret and_(bool yi) const;
    [[nodiscard]] BoolSecret and_(BoolSecret yi) const;
    [[nodiscard]] BoolSecret reconstruct() const;
    [[nodiscard]] bool get() const;

    // static methods for multiple usage
    static BoolSecret share(bool x);
    static BoolSecret xor_(bool xi, bool yi);
    static BoolSecret xor_(BoolSecret xi, BoolSecret yi);
    static BoolSecret and_(bool xi, bool yi);
    static BoolSecret and_(BoolSecret xi, BoolSecret yi);
};


#endif //MPC_PACKAGE_BOOLSECRET_H

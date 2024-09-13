//
// Created by 杜建璋 on 2024/9/12.
//

#ifndef MPC_PACKAGE_INTSECRET_H
#define MPC_PACKAGE_INTSECRET_H
#include "./Secret.h"
#include "../utils/Mpi.h"

class IntSecret: public Secret {
private:
    int _l{};
    int64_t _data{};
public:
    explicit IntSecret(int64_t x, int l);

    [[nodiscard]] IntSecret share() const;
    [[nodiscard]] IntSecret add(int64_t yi) const;
    [[nodiscard]] IntSecret multiply(int64_t yi) const;
    [[nodiscard]] IntSecret reconstruct() const;
    [[nodiscard]] int64_t get() const;

    // static methods for multiple usage
    static IntSecret share(int64_t x, int l);
    static IntSecret add(int64_t xi, int64_t yi, int l);
    static IntSecret multiply(int64_t xi, int64_t yi, int l);
};


#endif //MPC_PACKAGE_INTSECRET_H

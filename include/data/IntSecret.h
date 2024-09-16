//
// Created by 杜建璋 on 2024/9/12.
//

#ifndef MPC_PACKAGE_INTSECRET_H
#define MPC_PACKAGE_INTSECRET_H
#include "./Secret.h"
#include "../utils/Mpi.h"
#include <vector>

template<typename T>
class IntSecret: public Secret {
private:
    T _data{};
public:
    explicit IntSecret(T x);

    [[nodiscard]] IntSecret<T> share() const;
    [[nodiscard]] IntSecret<T> add(T yi) const;
    [[nodiscard]] IntSecret<T> add(IntSecret<T> yi) const;
    [[nodiscard]] IntSecret<T> multiply(T yi) const;
    [[nodiscard]] IntSecret<T> multiply(IntSecret<T> yi) const;
    [[nodiscard]] IntSecret<T> reconstruct() const;
    [[nodiscard]] T get() const;

    // static methods for multiple usage
    static IntSecret share(T x);
    static IntSecret share(IntSecret<T> x);
    static IntSecret add(T xi, T yi);
    static IntSecret add(IntSecret<T> xi, IntSecret<T> yi);
    static IntSecret multiply(T xi, T yi);
    static IntSecret multiply(IntSecret<T> xi, IntSecret<T> yi);
    static IntSecret sum(const std::vector<T>& xis);
    static IntSecret sum(const std::vector<IntSecret<T>>& xis, bool dummy);
    static IntSecret sum(const std::vector<T>& xis, const std::vector<T>& yis);
    static IntSecret sum(const std::vector<IntSecret<T>>& xis, const std::vector<IntSecret<T>>& yis, bool dummy);
};



#endif //MPC_PACKAGE_INTSECRET_H

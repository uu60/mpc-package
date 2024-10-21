//
// Created by 杜建璋 on 2024/9/12.
//

#ifndef MPC_PACKAGE_INTSECRET_H
#define MPC_PACKAGE_INTSECRET_H
#include "./Secret.h"
#include "../utils/Mpi.h"
#include "./BoolSecret.h"
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
    [[nodiscard]] IntSecret<T> convertToBool() const;
    [[nodiscard]] IntSecret<T> convertToArithmetic() const;
    [[nodiscard]] BoolSecret compare(T yi) const;
    [[nodiscard]] BoolSecret compare(IntSecret<T> yi) const;
    [[nodiscard]] T get() const;

    // static methods for multiple usage
    static IntSecret<T> share(T x);
    static IntSecret<T> share(IntSecret<T> x);
    static IntSecret<T> add(T xi, T yi);
    static IntSecret<T> add(IntSecret<T> xi, IntSecret<T> yi);
    static IntSecret<T> multiply(T xi, T yi);
    static IntSecret<T> multiply(IntSecret<T> xi, IntSecret<T> yi);
    static IntSecret<T> sum(const std::vector<T>& xis);
    static IntSecret<T> sum(const std::vector<IntSecret<T>>& xis);
    static IntSecret<T> sum(const std::vector<T>& xis, const std::vector<T>& yis);
    static IntSecret<T> sum(const std::vector<IntSecret<T>>& xis, const std::vector<IntSecret<T>>& yis);
    static IntSecret<T> product(const std::vector<T>& xis);
    static IntSecret<T> product(const std::vector<IntSecret<T>>& xis);
    static IntSecret<T> dot(const std::vector<T>& xis, const std::vector<T>& yis);
    static IntSecret<T> dot(const std::vector<IntSecret<T>>& xis, const std::vector<IntSecret<T>>& yis);
};

#endif //MPC_PACKAGE_INTSECRET_H

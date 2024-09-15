//
// Created by 杜建璋 on 2024/9/12.
//

#include "data/IntSecret.h"
#include "executor/share/IntShareExecutor.h"
#include "executor/share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h"

template<typename T>
IntSecret<T>::IntSecret(T x) {
    _data = x;
}

template<typename T>
IntSecret<T> IntSecret<T>::add(T yi) const {
    return IntSecret(Math::ring(_data + yi));
}

template<typename T>
IntSecret<T> IntSecret<T>::add(T xi, T yi, int l) {
    return IntSecret(xi + yi, l);
}

template<typename T>
IntSecret<T> IntSecret<T>::multiply(T yi) const {
    return IntSecret(RsaOtMultiplicationShareExecutor(_data, yi, false).execute(false)->result());
}

template<typename T>
IntSecret<T> IntSecret<T>::share() const {
    return IntSecret(IntShareExecutor(_data).xi());
}

template<typename T>
IntSecret<T> IntSecret<T>::reconstruct() const {
    return IntSecret(IntShareExecutor(0).zi(_data)->reconstruct()->result());
}

template<typename T>
IntSecret<T> IntSecret<T>::share(T x, int l) {
    return IntSecret(IntShareExecutor(x).xi(), l);
}

template<typename T>
IntSecret<T> IntSecret<T>::multiply(T xi, T yi, int l) {
    return IntSecret(RsaOtMultiplicationShareExecutor(xi, yi, false).execute(false)->result(), l);
}

template<typename T>
T IntSecret<T>::get() const {
    return _data;
}

template<typename T>
IntSecret<T> IntSecret<T>::sum(const std::vector<T>& xis, int l) {
    IntSecret<T> ret(0, l);
    for (T x : xis) {
        ret = ret.add(x);
    }
    return ret;
}

template<typename T>
IntSecret<T> IntSecret<T>::add(IntSecret<T> yi) const {
    return add(yi.get());
}

template<typename T>
IntSecret<T> IntSecret<T>::multiply(IntSecret<T> yi) const {
    return multiply(yi.get());
}

template<typename T>
IntSecret<T> IntSecret<T>::sum(const std::vector<T> &xis, const std::vector<T> &yis, int l) {
    IntSecret<T> ret(0, l);
    for (int i = 0; i < xis.size(); i++) {
        ret = ret.add(xis[i]).add(yis[i]);
    }
    return ret;
}






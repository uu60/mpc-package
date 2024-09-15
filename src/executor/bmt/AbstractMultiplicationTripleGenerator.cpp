//
// Created by 杜建璋 on 2024/8/30.
//

#include "executor/bmt/AbstractMultiplicationTripleGenerator.h"

template<typename T>
T AbstractMultiplicationTripleGenerator<T>::ai() const {
    return _ai;
}

template<typename T>
T AbstractMultiplicationTripleGenerator<T>::bi() const {
    return _bi;
}

template<typename T>
T AbstractMultiplicationTripleGenerator<T>::ci() const {
    return _ci;
}

template<typename T>
AbstractMultiplicationTripleGenerator<T> *AbstractMultiplicationTripleGenerator<T>::reconstruct() {
    return this;
}

template class AbstractMultiplicationTripleGenerator<bool>;
template class AbstractMultiplicationTripleGenerator<int8_t>;
template class AbstractMultiplicationTripleGenerator<int16_t>;
template class AbstractMultiplicationTripleGenerator<int32_t>;
template class AbstractMultiplicationTripleGenerator<int64_t>;
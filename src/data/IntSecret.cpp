//
// Created by 杜建璋 on 2024/9/12.
//

#include "data/IntSecret.h"
#include "executor/share/IntShareExecutor.h"
#include "executor/share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h"

IntSecret::IntSecret(int64_t x, int l) {
    _l = Math::normL(l);
    _data = Math::ring(x, _l);
}

IntSecret IntSecret::add(int64_t yi) const {
    return IntSecret(Math::ring(_data + yi, _l), _l);
}

IntSecret IntSecret::add(int64_t xi, int64_t yi, int l) {
    return IntSecret(xi + yi, l);
}

IntSecret IntSecret::multiply(int64_t yi) const {
    return IntSecret(RsaOtMultiplicationShareExecutor(_data, yi, _l, false).execute(false)->result(), _l);
}

IntSecret IntSecret::share() const {
    return IntSecret(IntShareExecutor(_data, _l).xi(), _l);
}

IntSecret IntSecret::reconstruct() const {
    return IntSecret(IntShareExecutor(0, _l).zi(_data)->reconstruct()->result(), _l);
}

IntSecret IntSecret::share(int64_t x, int l) {
    return IntSecret(IntShareExecutor(x, l).xi(), l);
}

IntSecret IntSecret::multiply(int64_t xi, int64_t yi, int l) {
    return IntSecret(RsaOtMultiplicationShareExecutor(xi, yi, l, false).execute(false)->result(), l);
}

int64_t IntSecret::get() const {
    return _data;
}





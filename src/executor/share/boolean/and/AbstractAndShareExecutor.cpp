//
// Created by 杜建璋 on 2024/8/29.
//

#include "executor/share/boolean/and/AbstractAndShareExecutor.h"
#include "utils/Math.h"
#include "utils/Mpi.h"
#include "executor/bmt/RsaOtTripleGenerator.h"

AbstractAndShareExecutor::AbstractAndShareExecutor(bool x) {
    _x = x;
    _x1 = Math::rand32(0, 1);
    _x0 = _x1 xor _x;

    // triple
    _a0 = Math::rand32(0, 1);
    _b0 = Math::rand32(0, 1);
    _c0 = _a0 and _b0;
}

void AbstractAndShareExecutor::compute() {
    // BMT
    obtainMultiplicationTriple();

    // process
    /*
     * For member variables, x represents part of own secret,
     * which means that for party[0], x represents x in paper,
     * for party[1], that is y in paper.
     *
     * For all the variables in this project, subscript of a
     * variable represents the party who will use that to
     * compute. For example, x0 is used by executor itself
     * while x1 is used by the other one.
     * */
    int64_t x0, y0, *self, *other;
    self = Mpi::rank() == 0 ? &x0 : &y0;
    other = Mpi::rank() == 0 ? &y0 : &x0;
    *self = _x0;
    Mpi::exchange(&_x1, other);
    int64_t e0 = _a0 xor x0;
    int64_t f0 = _b0 xor y0;
    int64_t e1, f1;
    Mpi::exchange(&e0, &e1);
    Mpi::exchange(&f0, &f1);
    int64_t e = e0 xor e1;
    int64_t f = f0 xor f1;
    int64_t z0 = Mpi::rank() * e * f xor f * _a0 xor e * _b0 xor _c0;
    int64_t z1;
    Mpi::exchange(&z0, &z1);
    _res = z0 xor z1;
}

std::string AbstractAndShareExecutor::tag() const {
    return "[And Boolean Share]";
}

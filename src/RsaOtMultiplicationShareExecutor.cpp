//
// Created by 杜建璋 on 2024/7/27.
//

#include "executor/share/arithmetic/RsaOtMultiplicationShareExecutor.h"

void RsaOtMultiplicationShareExecutor::obtainMultiplicationTriple() {
    generateRandomAB();

    computeU();
    computeV();
    computeC();

    if (_benchmark) {
        Log::i(BM_TAG + " OT RSA keys generation time: " + std::to_string(_otRsaGenerationTime) + " ms.");
        Log::i(BM_TAG + " OT RSA encryption time: " + std::to_string(_otRsaEncryptionTime) + " ms.");
        Log::i(BM_TAG + " OT RSA decryption time: " + std::to_string(_otRsaDecryptionTime) + " ms.");
        Log::i(BM_TAG + " OT MPI transmission and synchronization time: " + std::to_string(_otMpiTime) + " ms.");
        Log::i(BM_TAG + " OT total computation time: " + std::to_string(_otEntireComputationTime) + " ms.");
    }
}

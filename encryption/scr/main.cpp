//
// Created by Maria_Dron on 3/22/2019.
//

#include <iostream>
#include "keyGeneration/keyGeneration.h"
#include "keyGeneration/keyGeneration.cpp"
#include "encrypt/Encryption.h"
#include "encrypt/Encryption.cpp"

typedef unsigned long u32;

int main() {
    u32 ctx = (u32)1355;
    auto* keyGenerationObj = new keyGeneration();
    Keys keys = keyGenerationObj->GenKeys(ctx);

    std::cout << "f = " << std::endl;
    for (int i = 0; i < polynomialGFSize; i++)
        std::cout << keys.f[i] << ", ";

    std::cout << "\nh = " << std::endl;
    for (int i = 0; i < polynomialGFSize; i++)
        std::cout << keys.h[i] << " ";

    int m[881]= {};
    auto* encryptionObj = new Encryption();
    encryptionObj->Encrypt(ctx, m, keys.h);

    return 0;
}
//
// Created by Maria_Dron on 3/22/2019.
//

#include <iostream>
#include "keyGeneration/KeyGeneration.h"
#include "encrypt/Encryption.h"
#include "utils/const.h"

typedef unsigned long u32;

int main() {
    u32 ctx = (u32)1355;
    KeyGeneration* keyGenerationObj = new KeyGeneration();
    Keys keys = keyGenerationObj->GenKeys(ctx);

    std::cout << "f = ";
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
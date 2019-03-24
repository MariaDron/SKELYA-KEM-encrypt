//
// Created by Maria_Dron on 3/22/2019.
//

#include <iostream>
#include "keyGeneration/keyGeneration.h"
#include "keyGeneration/keyGeneration.cpp"
#include "encrypt/encryption.h"
#include "encrypt/encryption.cpp"

typedef unsigned long u32;

int main() {
    auto* keyGenerationObj = new keyGeneration();
    Keys keys = keyGenerationObj->GenKeys((u32)1355);

    std::cout << "f = " << std::endl;
    for (int i = 0; i < polinomSize; i++)
        std::cout << keys.f[i] << ", ";

    std::cout << "\nh = " << std::endl;
    for (int i = 0; i < polinomSize; i++)
        std::cout << keys.h[i] << " ";

    int m[881]= {};
    auto* encryptionObj = new encryption();
    encryptionObj->Encrypt(m, keys.h);

    return 0;
}
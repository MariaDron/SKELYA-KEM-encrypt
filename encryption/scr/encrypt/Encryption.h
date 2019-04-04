//
// Created by Maria_Dron on 3/24/2019.
//

#ifndef SKELYA_KEM_ENCRYPT_ENCRYPTION_H
#define SKELYA_KEM_ENCRYPT_ENCRYPTION_H

#include <stdlib.h>
#include <vector>
#include <string>

typedef unsigned long u32;
typedef unsigned char byte;

struct EncryptOutput {
    std::string status;
    int  E[881];
};

class Encryption {
    public:
        EncryptOutput Encrypt(u32 ctx, std::vector<int> m, std::vector<int> h);

};


#endif //SKELYA_KEM_ENCRYPT_ENCRYPTION_H

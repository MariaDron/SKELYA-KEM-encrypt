//
// Created by Maria_Dron on 3/24/2019.
//

#ifndef SKELYA_KEM_ENCRYPT_ENCRYPTION_H
#define SKELYA_KEM_ENCRYPT_ENCRYPTION_H

#include <stdlib.h>
#include <tuple>

typedef unsigned long u32;
typedef unsigned char byte;

struct EncryptOutput {
    std::string status;
    int  E[881];
};

class Encryption {

    int count(int polynomial[], int value);
    std::string* RE2OSP(int ring[], int ringSize, std::string *octetString);
    //std::string I2OSP(int A, int oLen);

    public:
        EncryptOutput Encrypt(u32 ctx, int m[] , int h[]);

};


#endif //SKELYA_KEM_ENCRYPT_ENCRYPTION_H

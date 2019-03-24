//
// Created by Maria_Dron on 3/19/2019.
//

#ifndef SKELYA_KEM_ENCRYPT_KEYGENERATION_H
#define SKELYA_KEM_ENCRYPT_KEYGENERATION_H

#include <stdlib.h>
#include <tuple>
#include <vector>

typedef unsigned char byte;
typedef unsigned long u32;

struct Keys {
    int  f[881];
    int  h[881];
};

class keyGeneration {

std::vector<int> R3Gen(u32 ctx, byte T);
int* rand(u32 ctx, byte commonSize);
byte ceil(byte value);
byte subst(byte buf, byte size);
int* unpack(byte value, byte buf);
byte inverse();

public:
    Keys GenKeys(u32 ctx);
};


#endif //SKELYA_KEM_ENCRYPT_KEYGENERATION_H

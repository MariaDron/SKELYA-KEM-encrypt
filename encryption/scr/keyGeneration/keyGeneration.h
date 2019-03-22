//
// Created by Maria_Dron on 3/19/2019.
//

#ifndef SKELYA_KEM_ENCRYPT_KEYGENERATION_H
#define SKELYA_KEM_ENCRYPT_KEYGENERATION_H

typedef unsigned char byte;
typedef unsigned long u32;

class keyGeneration {

std::tuple<int[], int[]> GenKeys(u32 ctx);
std::list<int> R3Gen(u32 ctx, byte T);
int* rand(u32 ctx, byte commonSize);
byte ceil(byte value);
byte subst(byte buf, byte size);
int* unpack(byte value, byte buf);
byte inverse();

};


#endif //SKELYA_KEM_ENCRYPT_KEYGENERATION_H

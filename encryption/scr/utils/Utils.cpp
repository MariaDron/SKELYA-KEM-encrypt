//
// Created by Maria_Dron on 3/25/2019.
//

#include "Utils.h"

int *Utils::random(u32 ctx, int commonSize, int *randBuf) {
    randBuf[commonSize];
    for (int i = 0; i < commonSize; i++)
        randBuf[i] = rand();
    return randBuf;
}

int *Utils::subst(int *buf, int size, int *newBuf) {
    newBuf[size];
    for (int i = 0; i < size; i++)
        newBuf[i] = buf[i];
    return newBuf;
}

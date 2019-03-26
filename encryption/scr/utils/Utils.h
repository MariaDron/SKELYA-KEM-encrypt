//
// Created by Maria_Dron on 3/25/2019.
//

#ifndef SKELYA_KEM_ENCRYPT_UTILS_H
#define SKELYA_KEM_ENCRYPT_UTILS_H

#include <stdlib.h>
#include <math.h>
#include <bitset>

using namespace std;
typedef unsigned long u32;

class Utils {

public:
    int* random(u32 ctx, int commonSize, int randBuf[]);
    int* subst(int buf[], int size,  int *newBuf);
};
#endif //SKELYA_KEM_ENCRYPT_UTILS_H

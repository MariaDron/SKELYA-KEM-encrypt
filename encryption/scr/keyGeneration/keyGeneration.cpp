//
// Created by Maria_Dron on 3/19/2019.
//

#include "keyGeneration.h"
#include "const.h"
#include <math.h>
#include <stdlib.h>
using namespace std;

std::tuple<int[], int[]> keyGeneration::GenKeys(u32 ctx) {
    int f[] = p * F + 1;
    int f_1[] = inverse(f);
    int h[] = p * f_1 * G;
    return std::make_tuple(f, h);
}

std::list<int> keyGeneration::R3Gen(u32 ctx, byte T) {
    std::vector<int> R;
    byte k = 0;
    byte j = 0;
    int values[] = {1, -1};
    byte maxInd = 1;
    byte i = n - T;

    byte sigSize = ceil((byte)(T / 8));
    byte indSize = ceil(n * c / 8);
    byte commonSize = sigSize + indSize;

    byte buf = rand(ctx, commonSize);
    byte sigBuf = subst(buf, 1, sigSize);
    byte indBuf = subst(buf, (byte) (1 + sigSize));
    int iSigBuf[] = unpack(1, sigBuf);
    int iIndBuf[] = unpack(c, indBuf);

    while  (i < n && j < n) {
        int ind = iIndBuf[j];
        j++;
        if (ind < max_ind - max_ind % i) {
            ind = ind % i;
            R.insert (myvector.begin(), i, R.at(ind));
            R.insert (myvector.begin(), ind, values[iSigBuf[k]]);
            k++;
            i++;
        }
    }
    if (k >= T) {
        break;
    }
    j = 0;

    while (j < n) {
        ind = iIndBuf [j];
        j++;
        if (ind < max_ind - max_ind % i) {
            value = value % j;
            //ind[j] = value;
            j++;
        }
    }
    return R;
}

byte keyGeneration::inverse() {
    return nullptr;
}

int* keyGeneration::rand(u32 ctx, byte commonSize) {
    int randBuf[commonSize];
    for (int i = 0; i < commonSize; i++)
        randBuf[i] = rand();
    return randBuf;
}

byte keyGeneration::ceil(byte value) {
    return (byte) trunc(value);
}

byte keyGeneration::subst(byte buf, byte size) {
    return 0;
}

int *keyGeneration::unpack(byte value, byte buf) {
    return nullptr;
}

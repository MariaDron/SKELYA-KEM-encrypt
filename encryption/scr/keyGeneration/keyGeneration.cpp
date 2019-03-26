//
// Created by Maria_Dron on 3/19/2019.
//

#include "keyGeneration.h"
#include "../utils/const.h"
#include <math.h>
#include <stdlib.h>
#include <tuple>
#include <vector>

using namespace std;

Keys keyGeneration::GenKeys(u32 ctx) {
    Keys keys = Keys();

    //f = F * p + 1
    for (int i = 0; i < polynomialGFSize; i++)
        keys.f[i] = F[i] * p;
    keys.f[0]++;

    //int f_1[] = inverse(keys.f);
    for (auto i = 0; i < polynomialGFSize; i++)
        keys.h[i] = keys.f[i] * p * G[i]; //f_1[i] * p * G[i];

    return keys;
}

byte keyGeneration::inverse(int *key) {
    return 0;
}

/*std::vector<int> keyGeneration::R3Gen(u32 ctx, byte T) {
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
        ind = iIndBuf[j];
        j++;
        if (ind < max_ind - max_ind % i) {
            value = value % j;
            iIndBuf[j] = value;
            j++;
        }
    }
    return R;
}*/

/*int* keyGeneration::rand(u32 ctx, byte commonSize) {
    int randBuf[commonSize];
    for (int i = 0; i < commonSize; i++)
        randBuf[i] = rand();
    return randBuf;
}*/
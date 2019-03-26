//
// Created by Maria_Dron on 3/24/2019.
//

#include "Encryption.h"
#include "../utils/const.h"
#include "../utils/Utils.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;


EncryptOutput Encryption::Encrypt(u32 ctx, int m[], int h[]) {
    Utils utils;
    EncryptOutput output;
    output.status = "ERROR";
    if (mLenBytes <= maxMsgLenBytes) {
        int b[db/8];
        utils.random(ctx, db/8, b);
        while (output.status == "ERROR") {
            int zero_count = bufferLenBytes - db / 8 - 1 - mLenBytes;
            std::string zero_string(zero_count, '0' );
            std::string octetString[(int) ceil((4 * qBit) / 8)];
            int ring[] = {8191, 1002, 1, 600};
            RE2OSP(ring, sizeof(ring) / sizeof(*ring), octetString);

            // M = b || mLenBytes || m || zero_string;
            std::string M;
            for (int i = 0; i < sizeof(b)/sizeof(*b); i++) {
                M.append(std::to_string(b[i]));
            }
            M.append(std::to_string(mLenBytes));
            for (int i = 0; i < sizeof(m)/sizeof(*m); i++) {
                M.append(std::to_string(m[i]));
            }
            M.append(zero_string);

            //MTrin = code3to2(M);

            int pkLen = sizeof(h)/sizeof(*h);

            // sData = OID || m || b || utils.subst(h, pkLen / 8);
            std::string sData;
            for (int i = 0; i < sizeof(OID)/sizeof(*OID); i++) {
                sData.append(std::to_string(OID[i]));
            }
            for (int i = 0; i < sizeof(m)/sizeof(*m); i++) {
                sData.append(std::to_string(m[i]));
            }
            for (int i = 0; i < sizeof(b)/sizeof(*b); i++) {
                M.append(std::to_string(b[i]));
            }
            int substH[pkLen / 8];
            utils.subst(h, pkLen / 8, substH);
            for (int i = 0; i < pkLen / 8; i++) {
                M.append(std::to_string(substH[i]));
            }

            int R4[sizeof(r)/sizeof(*r)];
            for (int i = 0; i < sizeof(r)/sizeof(*r); i++) {
                R4[i] = (r[i] + h[i] % q) % 4;
            }
            std::string oR4[sizeof(R4)/sizeof(*R4)];
            RE2OSP(R4, sizeof(R4)/sizeof(*R4), oR4);
            //mask = MGF(oR4);
            int m_[polynomialGFSize];
            for (int i = 0; i < polynomialGFSize; i++) {
                m_[i] = (MtrinEncrypt[i] + mask[i]) % p;
            }
            int c1 = count(m_, 1);
            int c2 = count(m_, -1);
            int c3 = count(m_, 0);
            if (c1 >= t && c2 >= t && c3 >= t) {
                output.status = "OK";
            }
        }
        /*e = R + m’ mod q;
        output.E = RQOS(e);*/
    }
    return output;
}

int Encryption::count(int *polynomial, int value) {
    int count = 0;
    for (int i = 0; i < sizeof(polynomial)/sizeof(*polynomial); i++) {
        if (polynomial[i] == value) {
            count++;
        }
    }
    return count;
}

/**
 * Ring Element to Octet String Primitive
 */
std::string *Encryption::RE2OSP(int ring[], int ringSize, std::string *octetString) {
    std::string octetPrimitives;
    std::string str;
    octetString[(int) ceil((ringSize * qBit) / 8)];

    for (int i = 0; i < ringSize; i++)
        octetPrimitives.append(std::bitset<qBit>(ring[i]).to_string());

    int i = 0;
    int j = 0;
    std::string octet;
    while (true) {
        if (i + 8 < octetPrimitives.size()) {
            octet = octetPrimitives.substr(i, 8);
            octetString[j] = octet;
        } else {
            std::string octet_str(8, '0');
            octet_str.replace(8 - (octetPrimitives.size() - i), octetPrimitives.size() - i,
                              octetPrimitives.substr(i, octetPrimitives.size()));
            octetString[j] = octet_str;
            return octetString;
        }
        i += 8;
        j++;
    }
}

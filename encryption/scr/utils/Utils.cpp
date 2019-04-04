//
// Created by Maria_Dron on 3/25/2019.
//

#include <iostream>
#include "Utils.h"

Const* constClass = new Const();

std::vector<int> Utils::random(u32 ctx, int commonSize) {
    std::vector<int> randBuf(commonSize);
    for (int i = 0; i < commonSize; i++)
        randBuf.push_back(rand());
    return randBuf;
}

std::vector<int> Utils::subst(const std::vector<int>& buf, int begin, int end) {
    std::vector<int> newBuf(end + 1);
    for (int i = begin; i <= end; i++)
        newBuf.push_back(buf.at(i));
    return newBuf;
}

int Utils::count(const std::vector<int>& polynomial, int value) {
    int count = 0;
    for (int i : polynomial) {
        if (i == value) {
            count++;
        }
    }
    return count;
}

bool Utils::is_zero(std::vector<std::string> zero) {
    for (std::string octet : zero) {
        std::bitset<8> bitOctet(octet);
        if (bitOctet.to_ulong() != 0)
            return false;
    }
    return true;
}

std::vector<int> Utils::polynomialMultiplication(std::vector<int> P1, std::vector<int> P2) {
    int max = P1.size() + P2.size() + 1;
    std::vector<int> mul(max);
    auto it = mul.begin();
    for (int i = P1.size(); i >= 0; i--) {
        for (int j = P2.size(); j >= 0; j--) {
            mul.insert(it, i + j, mul.at(i + j) + (P1[i] * P2[j]) % constClass->q);
        }
    }
    return mul;
}

/**
 * Ring Element to Octet String Primitive
 */
std::vector<std::string> Utils::RE2OSP(const std::vector<int>& ring) {
    std::string octetPrimitives;

    for (int i : ring) {
        octetPrimitives.append(std::bitset<8>(ring.at(i)).to_string());
    }

    std::vector<std::string> octetString;
    for (int i = 0; ; i += 8) {
        if (i + 8 < octetPrimitives.size()) {
            std::string octet = octetPrimitives.substr(i, 8);
            octetString.push_back(octet);
        }
        else {
            std::string octet(8, '0');
            octet.replace(8 - (octetPrimitives.size() - i), octetPrimitives.size() - i,
                          octetPrimitives.substr(i, octetPrimitives.size()));
            octetString.push_back(octet);
            break;
        }
    }

    return octetString;
}

std::vector<int> Utils::MGF(std::vector<std::string> octets) {
    vector<int> polynomialCoefficients;
    auto it = polynomialCoefficients.begin();
    /**
     * if needed
     */
    /*u32 ctx = 0;
    key = Hash(octets, octets.size());
    iv = hash256(OID, 3);
    ECRYPT_keysetup(&ctx, hash, k, 256);
    ECRYPT_ivsetup(&ctx, iv);
    Init256_(&ctx);*/
    u32 ctx = 0;
    int datalen = floor(2 * constClass->n / 5);
    byte count = 0;
    byte cur = 0;
    int i = 0;
    while (i < constClass->n) {
        std::vector<int> MGFStream = random(ctx, datalen);
        int j = 0;
        while (i < constClass->n - constClass->n % 5 && j < datalen) {
            int number = MGFStream[j];
            j++;
            if (number < 243) {
                int k = 0;
                while (k < 5) {
                    polynomialCoefficients.insert(it, i, number % 3);
                    number = number / 3;
                    if (polynomialCoefficients.at(i) == 2) {
                        polynomialCoefficients.insert(it, i, -1);
                    }
                    i++;
                    k++;
                }
            }
        }
        while (i < constClass->n && j < datalen) {
            int number = MGFStream.at(j);
            j++;
            if (number < 243) {
                int k = 0;
                while (k < 5) {
                    polynomialCoefficients.insert(it, i, number % 3);
                    number = number / 3;
                    i++;
                    if (i == constClass->n)
                        break;
                    k++;
                }
                if (i == constClass->n)
                    break;
            }
        }
        if (i == constClass->n)
            break;
    }
    return polynomialCoefficients;
}

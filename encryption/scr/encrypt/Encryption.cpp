//
// Created by Maria_Dron on 3/24/2019.
//

#include "Encryption.h"
#include "../utils/Utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;

EncryptOutput Encryption::Encrypt(u32 ctx, std::vector<int> m, std::vector<int> h) {
    Const* constClass = new Const();
    Utils* utils = new Utils();
    EncryptOutput output;
    output.status = "ERROR";
    std::vector<int> R(h.size());
    if (constClass->mLenBytes <= constClass->maxMsgLenBytes) {
        std::vector<int> b = utils->random(ctx, constClass->db/8);
        std::vector<int> m_(constClass->polynomialGFSize);
        while (output.status == "ERROR") {
            int zero_count = constClass->bufferLenBytes - constClass->db / 8 - 1 - constClass->mLenBytes;
            std::string zero_string(zero_count, '0' );

            // M = b || mLenBytes || m || zero_string;
            std::string M;
            for (int i : b) {
                M.append(std::to_string(i));
            }
            M.append(std::to_string(constClass->mLenBytes));
            for (int i : m) {
                M.append(std::to_string(i));
            }
            M.append(zero_string);

            //MTrin = code3to2(M);
            int pkLen = h.size();

            // sData = OID || m || b || utils.subst(h, pkLen / 8);
            std::string sData;
            for (byte i : constClass->OID) {
                sData.append(std::to_string(i));
            }
            for (int value : m) {
                sData.append(std::to_string(value));
            }
            for (int value : b) {
                sData.append(std::to_string(value));
            }
            std::vector<int> substH = utils->subst(h, 0, pkLen / 8 - 1);
            for (int value : substH) {
                sData.append(std::to_string(value));
            }

            for (int i = 0; i < h.size(); i++) {
                R.push_back(constClass->r.at(i) + h.at(i) % constClass->q);
            }

            std::vector<int> R4;
            int value;
            for (int i : R) {
                value = i % 4;
                if (value < 0)
                    value += 4;
                R4.push_back(value);
            }
            std::vector<std::string> oR4 = utils->RE2OSP(R4);
            std::vector<int> mask = utils->MGF(oR4);
            for (int i = 0; i < constClass->polynomialGFSize; i++) {
                m.push_back((constClass->MtrinEncrypt.at(i) + mask.at(i)) % constClass->p);
            }
            int c1 = utils->count(m_, 1);
            int c2 = utils->count(m_, -1);
            int c3 = utils->count(m_, 0);
            if (c1 >= constClass->t && c2 >= constClass->t && c3 >= constClass->t) {
                output.status = "OK";
            }
        }
        //e = R + m_ mod q;
        std::vector<int> e;
        e.reserve(m_.size());
        for (int i = 0; i < m_.size(); i++)
            e.push_back((R.at(i) + m_.at(i)) % constClass->q);
        //output.E = RQOS(e);
    }
    delete utils;
    return output;
}
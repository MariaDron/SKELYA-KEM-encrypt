#include <utility>

//
// Created by Maria_Dron on 3/31/2019.
//

#include <evntprov.h>
#include "Decryption.h"
#include "../utils/Utils.h"
#include "../utils/const.h"

DecryptOutput Decryption::Decrypt(const std::vector<int>& E, const std::vector<int>& h, std::vector<int> f) {
    Const* constClass = new Const();
    Utils* utils = new Utils();DecryptOutput output;
    output.status = "ERROR";
    std::vector<int> m;
    int pkLen = h.size();
    std::vector<int> e = OSRQ(E);
    std::vector<int> a = utils->polynomialMultiplication(std::move(f), e);
    std::vector<int> m_;
    for (int value : a) {
        m_.push_back(value % constClass->p);
    }
    int c1 = utils->count(m_, 1);
    int c2 = utils->count(m_, -1);
    int c3 = utils->count(m_, 0);
    if (c1 + c2 >= 2 * constClass->t && c3 >= constClass->t) {
        std::vector<int> R_;
        for (int i = 0; i < e.size(); i++) {
            R_.push_back((e.at(i) - m_.at(i)) % constClass->q);
        }
        std::vector<int> R4;
        for (int value : R_) {
            R4.push_back(value % 4);
        }
        std::vector<std::string> oR4 = utils->RE2OSP(R4);
        std::vector<int> mask = utils->MGF(oR4);
        std::vector<int> mTrin_;
        for (int i = 0; i < m_.size(); i++)
            mTrin_.push_back((m_.at(i) - mask.at(i)) % constClass->p);
        StructCode2to3 Mbin = code2to3(mTrin_);
        if (Mbin.status == "OK") {
            output.status = "ERROR";
            std::vector<std::string> M_ = BS2OSP(Mbin);
            /**
             * subst second parameter?
             * M_ is std::vector<std::string>
             */
            std::vector<std::string> b_ = utils->subst(M_, 1, constClass->db / 8);
            int m_len_ = utils->subst(M_, 1 + constClass->db / 8, 1);
            if (m_len_ <= constClass->maxMsgLenBytes) {
                m_ = utils->subst(M_, 2 + constClass->db / 8, m_len_);
                int zero_count = constClass->bufferLenBytes - constClass->db / 8 - 1 - m_len_;
                std::vector<std::string> zero = utils->subst(M_, constClass->db / 8 + 2 + m_len_, zero_count);
                bool res = utils->is_zero(zero);
                if (res) {
                    output.status = "OK";
                    //sData_ = OID || m’ || b’ || subst(h, 1, db / 8);
                    std::string sData;
                    for (byte oid : constClass->OID) {
                        sData.append(std::to_string(oid));
                    }
                    for (int value : m_) {
                        sData.append(std::to_string(value));
                    }
                    for (const std::string& value : b_) {
                        sData.append(value);
                    }
                    std::vector<int> substH = utils->subst(h, 0, pkLen / 8);
                    for (int i : substH) {
                        sData.append(std::to_string(i));
                    }
                    int sDataLen_ = 3 + m_len_ + 2 * constClass->db / 8;
                    //r_ = BPGM(sData_, sDataLen_);
                    std::vector<int> R;
                    for (int i = 0; i < constClass->r_.size(); i++)
                        R.push_back(constClass->r_.at(i) * h.at(i));
                    output.status = "ERROR";
                    if (R == R_) {
                        output.m = m_;
                        output.status = "OK";
                    }
                }
            }
        }
    }
    return output;
}

//
// Created by Maria_Dron on 3/25/2019.
//

#ifndef SKELYA_KEM_ENCRYPT_UTILS_H
#define SKELYA_KEM_ENCRYPT_UTILS_H

#include "const.h"
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <bitset>

using namespace std;
typedef unsigned long u32;

struct StructCode2to3 {
    std::vector<int> Mbin;
    std::string status;
};

class Utils {

public:
    std::vector<int> random(u32 ctx, int commonSize);
    std::vector<int> subst(const std::vector<int>& buf, int begin, int end);
    int count(const std::vector<int>& polynomial, int value);
    bool is_zero(std::vector<std::string> zero);
    std::vector<int> polynomialMultiplication(std::vector<int> P1, std::vector<int> P2);
    std::vector<std::string> RE2OSP(const std::vector<int>& ring);
    std::vector<int> MGF(std::vector<std::string> octets);
};
#endif //SKELYA_KEM_ENCRYPT_UTILS_H

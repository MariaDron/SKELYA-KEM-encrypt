//
// Created by Maria_Dron on 3/31/2019.
//

#ifndef SKELYA_KEM_ENCRYPT_DECRYPTION_H
#define SKELYA_KEM_ENCRYPT_DECRYPTION_H

#include <string>
#include <vector>

typedef unsigned long u32;
typedef unsigned char byte;

struct DecryptOutput {
    std::string status;
    std::vector<int> m;
};

class Decryption {
public:
    DecryptOutput Decrypt(const std::vector<int>& E, const std::vector<int>& h, std::vector<int> f);
};

#endif //SKELYA_KEM_ENCRYPT_DECRYPTION_H

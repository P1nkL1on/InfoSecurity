#ifndef FEISTEL_H
#define FEISTEL_H

#include <iostream>
#include <bitset>

namespace Feistel
{

    template <class T>
    inline T rightShift(const T val, const int shift){
        const int syzeof = sizeof(T) * 8;
        const int n = shift % syzeof;
        return (val >> n) | (val << (syzeof - n));
    }

    template <class T>
    inline T leftShift(const T val, const int shift){
        const int syzeof = sizeof(T) * 8;
        const int n = shift % syzeof;
        return (val << n) | (val >> (syzeof - n));
    }

    template <class T>
    inline void trace(const T c){
        const int syzeof = sizeof(T) * 8;
        std::cout << std::bitset<syzeof>(c)
            << std::endl;
        //  << "\t("<< syzeof << ")" << std::endl;
    }

    unsigned long long randomKey64();
    unsigned char F8 (const unsigned char L, const unsigned char key);
    unsigned int F(const unsigned int L, const unsigned int key);

    unsigned long long nextKey(const unsigned long long key0, const int iteration);

    void test();

    std::string code64(const std::string &message, const long long key0, const int nSteps);
    std::string decode64(const std::string &cryptedMessage, const long long key0, const int nSteps);

    std::string code64CBC(const std::string &message, const long long key0, const int nSteps, const long long IV);
    std::string decode64CBC(const std::string &cryptedMessage, const long long key0, const int nSteps, const long long IV);

    std::string code64CFB(const std::string &message, const long long key0, const int nSteps, const long long IV);
    std::string decode64CFB(const std::string &cryptedMessage, const long long key0, const int nSteps, const long long IV);

    std::string code8(const std::string &message, const long long key0, const int nSteps);
    std::string decode8(const std::string &cryptedMessage, const long long key0, const int nSteps);
}

#endif // FEISTEL_H

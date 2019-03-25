#pragma once
#include <QVector>
class rsa
{
private:
	static unsigned long long* Sundaram(unsigned long long n);
	static unsigned long long gcd(unsigned long long a, unsigned long long b);
    static unsigned long long bpow(unsigned long long x, unsigned long long n, unsigned long long m);
public:
    static QVector<unsigned long long> sundaram2(const unsigned long long n);
	static char* decrypt(char* Text, int textLength, unsigned long long e, unsigned long long n);
};

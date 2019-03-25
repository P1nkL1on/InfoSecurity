#include "stdafx.h"
#include "rsa.h"
#include <iomanip>
#include <cstring>
#include <iostream>
using namespace std;

// sundaram
QVector<unsigned long long> rsa::sundaram2(const unsigned long long n)
{/*
    unsigned long long i,j,k;

    QVector<unsigned long long> a = QVector<unsigned long long>(n/2, 0);
    QVector<unsigned long long> res;
    for (i = 1; 3 * i + 1 < n; i++){
        for (j = 1; (k = i + j + 2 * i*j) < n && j <= i; j++){
            a[k] = 1;
            //cout << k << endl;
        }
    }
    for (int i = 0; i < a.length(); ++i)
        if (!a[i])
            res << i;
    return res;*/
    QVector<unsigned long long> b;
    const unsigned long long st = 10000;//n / 1000;
    int progress = 0;

    for (int i = 1; i < n; ++i){
        bool isOk = true;
        for (int j = 2; j < i; ++j)
            if (i % j == 0){
                isOk = false;
                break;
            }
        if (isOk){
            b << i;
            //            cout << i << endl;
            int x = i / st;
            if (x > progress){progress = x; cout << x <<"\t\t/" << n/st << endl;}
        }
    }
    return b;
}

unsigned long long* rsa::Sundaram(unsigned long long n)
{
    //const long long N = static_cast<long long>(n / (sizeof(long long)) - 1);
    //const long long N = n;
    //    n /= 128;
    //    n = (n - 1) / 2;//std::llround((n - 1) / 2);
    n = n / 4 + 3;
    unsigned long long *a = new unsigned long long[n];
    int	i, j, k;
    memset(a, 0, sizeof(unsigned long long) * n);

    for (i = 1; 3 * i + 1 < n; i++){
        for (j = 1; (k = i + j + 2 * i*j) < n && j <= i; j++){
            a[k] = 1;
            //cout << k << endl;
        }
    }
    int count = 0;
    for (i = 1; i < n; i++){
        if (a[i] == 0)
            a[count++] = 2 * i + 1;
    }

    unsigned long long* b = new unsigned long long[count + 1];
    b[0] = count;
    cout << "Sundaram method = [ ";
    for (i = 1; i < count; i++){
        b[i] = a[i];
        cout << b[i] << ", ";
    }
    cout << "..], count = " << b[0]  << endl;
    delete[] a;
    return b;
}

// NOD
unsigned long long rsa::gcd(unsigned long long a, unsigned long long b)
{
    return b ? gcd(b, a % b) : a;
}

unsigned long long rsa::bpow(unsigned long long x, unsigned long long n, unsigned long long m)
{
    unsigned long long count = 1;
    if (!n) return 1;
    while (n) {
        if (n % 2 == 0) {
            n /= 2;
            x *= x;
            x %= m;
        }
        else {
            n--;
            count *= x;
            count %= m;
        }
    }
    return count % m;
}

char* rsa::decrypt(char* Text, int textLength, unsigned long long e, unsigned long long n)
{
    //    unsigned long long a0 = 0, d0 = 0;
    //    unsigned long long* primeNumbers = Sundaram(n);

    //    if (primeNumbers[0] < 2)
    //        return 0;

    //    unsigned long long d = 0;
    //    unsigned long p = 0, q = 0;
    //    unsigned long long fn = 0;
    //    const int l = static_cast<int>(primeNumbers[0]);
    //    for (int i = 1; i < l; ++i)
    //        for (int j = i + 1; j < l; ++j)
    //            if (primeNumbers[i] * primeNumbers[j] == n){
    //                // cout << "Found a p,q: " << primeNumbers[i] << " " << primeNumbers[j] << endl;
    //                p = primeNumbers[i];
    //                q = primeNumbers[j];
    //                fn = (p - 1) * (q - 1);
    //                unsigned long long tmpD = 2;
    //                while((tmpD * e) % fn != 1)
    //                    ++tmpD;
    //                d = tmpD;
    //                break;
    //            }
    unsigned long long p = 2432371, q = 212885833, d, //p = 2431967, q = 193707721, d,
            fn = (p - 1) * (q - 1);
    //    unsigned long long tmpD = 2;
    //    while((tmpD * e) % fn != 1)
    //        ++tmpD;
    // tmpD * e = fn * m + 1

    unsigned long long tmpM = 0;

    while((fn * (++tmpM) + 1) % e != 0);

    d = (tmpM * fn + 1) / e;

    cout << "Found a d, where (d*e)%f(n) == 1: " << d << endl;
    cout << "Proof: " << d << "*" << e << " mod " << fn << " = " << (d * e) << " mod " << fn << " = " << (d * e)%fn << endl;

    //pxq = 2432371×212885833; d = 421848835 4.87sec
    //    unsigned long p = 2432371, q = 212885833;
    //    unsigned long long d = 421848835;
    //while (true)
    //{
    //	if ((e*d) % ((q-1)*(p-1)) == 1)
    //	{
    //		break;
    //	}
    //	d++;
    //}
    //    unsigned long long prev, curr = 0, decr = 0;
    //    int i = 0, j = 0, a = 0, buffSize = 20;
    //    char* decrText = new char[textLength * 2];
    //    char* buff = new char[buffSize];

    //    int bufferHead = 0;
    //    while (i < textLength)
    //    {
    //        //cout << i << " " << curr << " < " << n << endl;
    //        //curr = curr * 10 + (Text[i++] - 48); // -48 потому что ascii
    //        prev = curr;
    //        curr = curr * 10 + (Text[i++] - 48);
    //        j++;
    //        if (curr > n){
    //            //Расшифровка полученного кода по формуле mi = (ci^d)%n
    //            decr = bpow(prev, d, n);
    //            cout << "decrypt: " << prev << " -> " << decr << endl;// << ", (d,n) = " << d << ", " << n << endl;

    //            decr *= 10;
    //            do{
    //                cout << decr % 100 << "  "<< char(decr % 100) << endl;
    //                decr /= 100;
    //            } while ( decr );

    //            i--;
    //            curr = 0;
    //            j = 0;
    //        }
    //        buff[0] = 0;
    //    }
    //    return decrText;
    unsigned long long prev, curr = 0, decr;
    int i = 0, j = 0, a = 0, buffSize = 20;
    char* decrText = new char[textLength * 2];
    char* buff = new char[buffSize];

    while (i < textLength)
    {
        prev = curr;
        //curr = curr * 10 + (Text[i++] - 48); // -48 потому что ascii
        curr = curr * 10 + (Text[i++] - 48);
        j++;
        if (curr > n)
        {
            //Расшифровка полученного кода по формуле mi = (ci^d)%n
            decr = bpow(prev, d, n);
            //Запись в массив char
            i--;
            _itoa_s(decr, buff, buffSize, 20);
            strcpy_s(decrText, buffSize, buff);
            curr = 0;
            j = 0;
        }
        buff[0] = 0;
    }
    return decrText;
}

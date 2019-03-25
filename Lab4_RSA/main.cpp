#include <QCoreApplication>
#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>


bool isPrime(unsigned long long prime);
unsigned long long calculateE( unsigned long long t );
unsigned long long greatestCommonDivisor( unsigned long long e, unsigned long long t );
unsigned long long calculateD( unsigned long long e, unsigned long long t );
unsigned long long encrypt( unsigned long long i, unsigned long long e, unsigned long long n );
unsigned long long decrypt(unsigned long long i, unsigned long long d, unsigned long long n );
unsigned long long mult(unsigned long long x , unsigned long long y, unsigned long long m);
unsigned long long calculateModuleMult(unsigned long long a, unsigned long long b, unsigned long long c);
void calculateQnP(unsigned long long n);

unsigned long long p, q, n, fi, e, d;

int law (){
    unsigned long long encryptedText[100], decryptedText[100];
    memset(encryptedText, 0, sizeof(encryptedText));
    memset(decryptedText, 0, sizeof(decryptedText));

    std::string msg;
    q = p = 4;
    do { std::cout << "Enter p: "; std::cin >> p; } while (!isPrime(p));
    do { std::cout << "Enter q: "; std::cin >> q; } while (!isPrime(q));

    n = p * q;
    std::cout << "n = p*q = " << n << std::endl<< std::endl;
    calculateQnP(n);

    fi = ( p - 1 ) * ( q - 1 );
    std::cout << "f(n) = (p-1) * (q-1) = t = " << fi << std::endl<< std::endl;

    e = calculateE( fi );
    std::cout << "e = " << e << std::endl<< std::endl;

    d = calculateD( e, fi );
    std::cout << "d*e = 1 (mod f(n)), d = "<< d << std::endl<< std::endl;

    std::cout << "public key is (n = " << n << ", e = " << e << ")" << std::endl << std::endl;

    std::cout << "private key is (n = " << n << ", d = " << d << ")" << std::endl << std::endl;

    std::cout << "\nEnter Message to be encryped: ";

    std::cin.ignore();

    std::getline( std::cin, msg );
    std::cout << "msg = " << msg << std::endl;

    for (unsigned long long i = 0; i < msg.length(); i++)
        encryptedText[i] = encrypt( msg[i], e, n);

    std::cout << "\ncrypted = ";

    for ( unsigned long long i = 0; i < msg.length(); i++ )
        printf( "%c", (char)encryptedText[i] );

    for (unsigned long long i = 0; i < msg.length(); i++)
        decryptedText[i] = decrypt(encryptedText[i], d, n);

    std::cout << "\n\ndecrypted = ";

    for (unsigned long long i = 0; i < msg.length(); i++)
        printf( "%c", (char)decryptedText[i] );

    std::cout << std::endl << std::endl;
}

int hack(){
    unsigned long long encryptedText[100], decryptedText[100];
    memset(encryptedText, 0, sizeof(encryptedText));
    memset(decryptedText, 0, sizeof(decryptedText));

    std::string msg;
    q = p = -1;

    n = 471090785117207;
    std::cout << "n = " << n << std::endl << std::endl;
    calculateQnP(n);
    std::cout << std::endl << "p * q = " << p << " * " << q << " = " << std::endl << q * p << " == " << n << std::endl << std::endl;

    fi = ( p - 1 ) * ( q - 1 );
    std::cout << "f(n) = (p-1) * (q-1) = t = " << fi << std::endl<< std::endl;

    e = 12377;
    std::cout << "e = " << e << std::endl<< std::endl;

    d = calculateD( e, fi );
    std::cout << "d*e = 1 (mod f(n)), d = "<< d << std::endl<< std::endl;

    std::cout << "public key is (n = " << n << ", e = " << e << ")" << std::endl << std::endl;

    std::cout << "private key is (n = " << n << ", d = " << d << ")" << std::endl << std::endl;

    std::cout << "\nEnter Message to be encryped: ";

    std::getline( std::cin, msg );
    std::cout << "msg = " << msg << std::endl;

    for (unsigned long long i = 0; i < msg.length(); i++)
        encryptedText[i] = encrypt( msg[i], e, n);

    std::cout << "\ncrypted = ";

    for ( unsigned long long i = 0; i < msg.length(); i++ )
        printf( "%c", (char)encryptedText[i] );

    for (unsigned long long i = 0; i < msg.length(); i++)
        decryptedText[i] = decrypt(encryptedText[i], d, n);

    std::cout << "\n\ndecrypted = ";

    for (unsigned long long i = 0; i < msg.length(); i++)
        printf( "%c", (char)decryptedText[i] );

    std::cout << std::endl << std::endl;
}

int main( )
{
    hack();
    //p = 2431967;
    //q = 193707721;
    //e = 12377;
    return 0;
}

bool isPrime( unsigned long long prime)
{
    unsigned long long i, j;

    j = (unsigned long long)sqrt((long double)prime);

    for ( i = 2; i <= j; i++)
        if ( prime % i == 0 ){
            std::cout << prime << " is not prime, at least: % " << i << " == 0" << std::endl;
            return false;
        }

    return true;
}

unsigned long long calculateE( unsigned long long t )
{
    // e ( 1 < e < t ) // взаимно простое со значением функции Эйлера (t)

    unsigned long long e;

    for ( e = 2; e < t; e++ )
        if (greatestCommonDivisor( e, t ) == 1 )
            return e;

    return -1;
}

unsigned long long greatestCommonDivisor( unsigned long long e, unsigned long long t )
{
    while ( e > 0 )
    {
        unsigned long long myTemp;

        myTemp = e;
        e = t % e;
        t = myTemp;
    }

    return t;
}

unsigned long long calculateD( unsigned long long e, unsigned long long t)
{
    // Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))

    unsigned long long d;
    unsigned long long k = 1;

    while ( 1 )
    {
        k = k + t;

        if ( k % e == 0)
        {
            d = (k / e);
            return d;
        }
    }

}

unsigned long long mult(unsigned long long x , unsigned long long y, unsigned long long m)
{
    unsigned long long res = 0;
    while (y > 0)
    {
        if (y % 2 == 1)
        {
            y--;
            res = (res + x) % m;
        }
        x = (x + x) % m;
        y /= 2;
    }
    return res;

}

unsigned long long calculateModuleMult(unsigned long long a, unsigned long long b, unsigned long long c){
    //std::cout << a << "^" << b << " %" << c;
    unsigned long long multRes = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            b--;
            multRes = mult(multRes , a, c);
        }
        b /= 2;
        a = mult(a , a, c);
    }
    //std::cout << " = " << multRes << std::endl;
    return multRes;
}

void calculateQnP(unsigned long long n)
{
    // Print the number of 2s that divide n
    while (n%2 == 0)
    {
        q = 2;
        printf("%d ", 2);
        n = n/2;
    }

    // n must be odd at this point.  So we can skip
    // one element (Note i = i +2)
    for (unsigned long long i = 3; i <= sqrt(n); i = i+2)
    {
        // While i divides n, print i and divide n
        while (n%i == 0)
        {
            p = i;
            printf("p = %d ", i);
            n = n/i;
        }
    }

    // This condition is to handle the case when n
    // is a prime number greater than 2
    if (n > 2){
        q = n;
        printf ("q = %d ", n);
    }
}

unsigned long long encrypt( unsigned long long i, unsigned long long e, unsigned long long n )
{
    unsigned long long current, result;

    current = i;
    result = 1;
    result = calculateModuleMult(current, e, n);
    return result;
}

unsigned long long decrypt(unsigned long long i, unsigned long long d, unsigned long long n)
{
    unsigned long long current, result;

    current = i;
    result = 1;
    result = calculateModuleMult(current, d, n);
    return result;
}



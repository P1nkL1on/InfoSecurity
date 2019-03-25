#include <QCoreApplication>
#include "stdafx.h"
#include "RSA.h"
#include <iostream>
#include <cstdlib>
using namespace std;


int main (){
//    rsa::sundaram2(471090785117207);
    const int maxMessageBufferSize = 45;//100;
    char *cryptedMessage = //"1409369299276511009334920011486253711170338478810154561374471402080505247451146040719755";
            "314999112281065205361706341517321987491098667";
    //char *cryptedMessage = new char[maxMessageBufferSize];

    unsigned long long n=0, e=0;

//    cout << "Enter text:" << endl;
//    cin.getline(message, maxMessageBufferSize);
//    cout << "Enter e:" << endl;
//    cin >> e;
//    cout << "Enter n:" << endl;
//    cin >> n;


    n = static_cast<unsigned long long>(471090785117207/*187*/);
    e = static_cast<unsigned long long>(12377/*101*/);

//    n = static_cast<unsigned long long>(517817326500043);
//    e = static_cast<unsigned long long>(12331);
    char* message = rsa::decrypt(cryptedMessage, maxMessageBufferSize, e, n);

    printf("\nMessage = %s", message);

    cin >> e;
    return 0;
}

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}

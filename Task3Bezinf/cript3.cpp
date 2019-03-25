// cript3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RSA.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//13)
//n = 517817326500043     e = 12331
//ив = 1409369299276511009334920011486253711170338478810154561374471402080505247451146040719755

int main()
{
	const int MAX = 100;
	char *Text = new char[MAX];
	unsigned long long n=0, e=0;

	cout << "Please enter the Text. Use <Enter> button when done." << endl;
	cin.getline(Text, MAX);

	//cout << "Please enter the e. Use <Enter> button when done." << endl;
	//cin >> e;

	//cout << "Please enter the n. Use <Enter> button when done." << endl;
	//cin >> n;

	n = static_cast<unsigned long long>(517817326500043);
	e = static_cast<unsigned long long>(12331);
	char* text = rsa::Decrypt(Text, MAX, e, n);

	printf("%s \n", text);

	cin >> e;
    return 0;
}


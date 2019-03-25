#include <QCoreApplication>
#include <iostream>
#include <QTextStream>
#include <QTextCodec>

#include "cesardecoder.h"

using namespace std;

int main(){
    QTextStream os(stdout);
    os.setCodec(QTextCodec::codecForName("cp866"));

    QString orig = "щ зсдлъэд фцяб";

    for (int i = 0; i < 33; ++i)
        os << i << " : " << Cesar::cycleRusText(orig, i) << endl;

    return 0;
}

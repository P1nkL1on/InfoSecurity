#ifndef CESARDECODER_H
#define CESARDECODER_H
#include <QString>

namespace Cesar{
    QString getRussianAlphabet ();

    QString cycleRusText(const QString enterString, const int offset);
}

#endif // CESARDECODER_H

#include "cesardecoder.h"

QString Cesar::getRussianAlphabet()
{
    return "абвгдеёжзиклмнопрстуфхцчшщъыьэюя";
}

QString Cesar::cycleRusText(const QString enterString, const int offset)
{
    QString tmp;
    const QString a = getRussianAlphabet();

    for (int i = 0; i < enterString.length(); ++i)
        if (a.indexOf(enterString.at(i)) >= 0)
            tmp += a.at((a.indexOf(enterString.at(i)) + offset) % a.length());
        else
            tmp += enterString.at(i);

    return tmp;
}

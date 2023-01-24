#pragma once
#ifndef PARSETEXT_H
#define PARSETEXT_H
#include <QString>



class ParseText
{
public:
    ParseText();
    bool change(QString);
    QString subs(QString);
    QString getText();
private:
    QString text;//Последний текст
    QString preText; //Текст с правкой примера
    qint32 pos;//позиция указателя поиска
};

#endif // PARSETEXT_H

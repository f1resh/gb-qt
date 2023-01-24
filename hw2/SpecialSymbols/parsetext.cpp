#include "parsetext.h"

#define MIN(a, b) (a < b) ? a : b

ParseText::ParseText()
{
    text = "";
    preText = "";
    pos = 0;
}

bool ParseText::change(QString istr)
{
    qint32 length = MIN(MIN(text.length(), istr.length()), pos);
    preText = "";
    for (qint32 i = 0; i < length; i++) {
        if (text[i] != istr[i]) {
            pos = i;
            break;
        }
    }
    const QChar *arStr = istr.constData();
    qint32 ppos = 0, lastp = -1; // курсор на начало символа, с которого будет осуществлять поиск метку #@

    bool chg = false; // есть изменения текста?
    for (qint32 fnd = istr.indexOf("#@", pos); // поиск первого примера в тексте
        fnd != -1 && lastp != pos; // -1 - означает, что в строке нет (больше) примеров
        fnd = istr.indexOf("#@", pos)
        ) {

            preText.insert(preText.length(), &arStr[ppos], fnd - ppos); // копируем текст до примера
            lastp = pos;
            pos = fnd;
            //EDIT - replace with spec symbols!
            int r = istr.indexOf('@', fnd+2);//если есть равенство, то пример завершен
            int space = istr.indexOf(' ', fnd);
            if ((r < space || space == -1) && r != -1) { // проверяем, что равно для текущего примера, а не следующего
                QString exampl = "";
                exampl.insert(0, &arStr[fnd], r - fnd + 1);
                QString rez = subs(exampl);
                preText += rez;
                pos = r + 1;
                ppos = r + 1;
                chg = true;
            }

        }

        preText.insert(preText.length(), &arStr[pos], istr.length() - pos); // дописываем оставшийся текст

    if (pos > preText.length()) pos = preText.length();

    return chg;
}

QString ParseText::subs(QString str)
{
    QString temp = str.mid(2,str.length()-3);
    if (temp == "RUB") return "₽";
    if (temp == "EURO") return "€";
    if (temp == "COPYRIGHT") return "©";
    if (temp == "PERMILLE") return "‰";
    return str;

}

QString ParseText::getText()
{
    text = preText;
    return text;
}



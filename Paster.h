#ifndef PASTER_H
#define PASTER_H

#include "Utils.h"

#include <QObject>

#include <windows.h>
#include <iostream>


class Paster : public QObject
{
    Q_OBJECT

public:
    explicit Paster(QObject *parent = nullptr);

    static void sendInputString(const std::wstring &str);
    static std::wstring getClipboardText();
    static void pasteClipboard();
};

#endif // PASTER_H

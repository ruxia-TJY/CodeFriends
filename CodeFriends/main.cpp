/*
MIT License

Copyright (c) 2023 ruxia.TJY

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include "CodeFriends.h"
#include "constant.h"
#include <QtWidgets/QApplication>
#include <qfont.h>
#include <qtranslator.h>
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("CodeFriends");
    a.setApplicationDisplayName("CodeFriends");
    a.setApplicationVersion(VERSION);
    
    QTranslator qtTranslator;
    QLocale locale;
    switch (locale.language())
    {
    case QLocale::English:
        qtTranslator.load(":/qm/Translation/Translation_en.qm");
        break;
    case QLocale::Chinese:
        qtTranslator.load(":/qm/Translation/Translation_zh_CN.qm");
        break;
    default:
        qtTranslator.load(":/qm/Translation/Translation_zh_CN.qm");
        break;
    }
    
    a.installTranslator(&qtTranslator);
    
    Config config;
    a.setFont(config.Font_default);
   
    CodeFriends w;
    w.show();
    return a.exec();
}

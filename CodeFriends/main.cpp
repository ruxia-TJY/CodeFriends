#include "CodeFriends.h"
#include "constant.h"
#include <QtWidgets/QApplication>
#include <qfont.h>
#include <qtranslator.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("CodeFriends");
    a.setApplicationDisplayName("CodeFriends");
    a.setApplicationVersion(VERSION);

    QTranslator qtTranslator;
    qtTranslator.load(":/qm/Translation/Translation_zh_CN.qm");
    //qtTranslator.load(":/qm/Translation/Translation_en.qm");
    a.installTranslator(&qtTranslator);

    QFont font = a.font();
    font.setPointSize(20);
    a.setFont(font);


    CodeFriends w;
    w.show();
    return a.exec();
}

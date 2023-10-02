#include "CodeFriends.h"
#include "constant.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("CodeFriends");
    a.setApplicationDisplayName("CodeFriends");
    a.setApplicationVersion(VERSION);

    CodeFriends w;
    w.show();
    return a.exec();
}

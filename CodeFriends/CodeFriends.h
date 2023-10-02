#pragma execution_character_set("utf-8");

#include <QtWidgets/QMainWindow>
#include <qplaintextedit.h>
#include <qaction.h>
#include <qtoolbar.h>
#include <qdebug.h>
#include <qmenu.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qdockwidget.h>
#include <qlistwidget.h>
#include <qgridlayout.h>
#include <qstatusbar.h>
#include "ui_CodeFriends.h"
#include "Highlighter.h"
#include "CodeEditor.h"


QT_BEGIN_NAMESPACE
class QTextEdit;
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class CodeFriends : public QMainWindow
{
    Q_OBJECT

public:
    CodeFriends(QWidget *parent = nullptr);
    ~CodeFriends();

public slots:
    

private:
    Ui::CodeFriendsClass ui;

    void setupEditor();
    void setupUI();
    void setupToolBar();

    CodeEditor* editor;
    Highlighter* highlighter;

    
};

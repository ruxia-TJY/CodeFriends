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
#include <qlineedit.h>
#include <qfileinfo.h>
#include <qdatetime.h>
#include <qstringlist.h>

#include "ui_CodeFriends.h"
#include "Highlighter.h"
#include "CodeEditor.h"
#include "database.h"

#include "UiAbout.h"


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

    void closeEvent(QCloseEvent* event);

    void setupEditor();
    void setupUI();
    
    void setupLibrary();

    QLineEdit* titleline;
    CodeEditor* editor;
    Highlighter* highlighter;
    Database* db;

    QComboBox* cB_lib;
    QLineEdit* lE_search;
    
    QListWidget* lW_DB;
    
    UiAbout* uiabout;

private slots:
    void add_code();
    void save_code();
    void delete_code();
    void refresh_code();

    void show_ui_about();
};

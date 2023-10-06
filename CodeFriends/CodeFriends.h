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
#include <qtimer.h>

#include "ui_CodeFriends.h"
#include "Highlighter.h"
#include "CodeEditor.h"
#include "database.h"

#include "UiAbout.h"
#include "UiSetting.h"

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

    // 当前文本框是否为改变
    bool editor_changed_mode = false;

    void closeEvent(QCloseEvent* event);

    void setupEditor();
    void setupUI();
    
    void setupLibrary();
    void setupTitleList();

    void timeUpdate();

    UiAbout* uiabout;
    UiSetting* uisetting;

    QLineEdit* lE_title;
    CodeEditor* editor;
    Highlighter* highlighter;
    Database* db;

    QComboBox* cB_lib;
    QLineEdit* lE_search;
    
    QListWidget* lW_DB;
    QLabel* lbl_title_list_count;
    

    QTimer* timer;
    QDateTime* current_datetime;

    QLabel* lbl_attachment_info;
    QLabel* lbl_current_datetime;
    QLabel* lbl_create_datetime;
    QLabel* lbl_update_datetime;

private slots:
    void add_code();
    void save_code();
    void delete_code();
    void refresh_code();

    void search_title();

    void readCodeData();

    void show_ui_about();
    void show_ui_setting();
};

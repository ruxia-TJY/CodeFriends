#include "CodeFriends.h"

CodeFriends::CodeFriends(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    this->resize(QSize(2000, 1000));
    
    setupUI();
    setupEditor();
    setCentralWidget(editor);
}

CodeFriends::~CodeFriends()
{}

//! [1]
void CodeFriends::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor = new CodeEditor;
    editor->setFont(font);

    highlighter = new Highlighter(editor->document());
}

void CodeFriends::setupUI()
{
    statusBar()->showMessage("正在刷新界面...", 1000);
    // toolBar_edit
    QToolBar* toolBar_edit = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar_edit);

    //toolBar_edit->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    //toolBar_edit->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    toolBar_edit->setWindowTitle("edit");
    
    QAction* pb_add = new QAction(QIcon(":/icon/resource/PNG_add.png"), "add", this);
    QAction* pb_save = new QAction(QIcon(":/icon/resource/PNG_save.png"), "save", this);
    QAction* pb_delete = new QAction(QIcon(":/icon/resource/PNG_delete.png"), "delete", this);
    QAction* pb_refresh = new QAction(QIcon(":/icon/resource/PNG_refresh.png"), "refresh", this);
    
    toolBar_edit->addAction(pb_add);
    toolBar_edit->addAction(pb_save);
    toolBar_edit->addAction(pb_delete);
    toolBar_edit->addAction(pb_refresh);

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar_edit->addWidget(spacer);

    QAction* pb_attachment_import = new QAction("导入附件", this);
    QAction* pb_attachment_export = new QAction("导出附件", this);

    QMenu* pb_attachment_menu = new QMenu("附件");
    pb_attachment_menu->addAction(pb_attachment_import);
    pb_attachment_menu->addAction(pb_attachment_export);
    
    QToolButton* pb_attachment_btn = new QToolButton();
    pb_attachment_btn->setIcon(QIcon(":/icon/resource/PNG_attachment.png"));
    pb_attachment_btn->setPopupMode(QToolButton::InstantPopup);
    pb_attachment_btn->setMenu(pb_attachment_menu);
    
    toolBar_edit->addWidget(pb_attachment_btn);

    QAction* pb_about = new QAction("关于", this);
    QAction* pb_setting = new QAction(QIcon(":/icon/resource/PNG_setting.png"), "设置", this);

    QMenu* pb_help_menu = new QMenu("帮助");
    pb_help_menu->addAction(pb_setting);
    pb_help_menu->addSeparator();
    pb_help_menu->addAction(pb_about);

    QToolButton* pb_help_btn = new QToolButton();
    pb_help_btn->setIcon(QIcon(":/icon/resource/PNG_help.png"));
    pb_help_btn->setPopupMode(QToolButton::InstantPopup);
    pb_help_btn->setMenu(pb_help_menu);

    toolBar_edit->addWidget(pb_help_btn);
    
    this->addToolBarBreak();

    // toolBar_search
    QToolBar* toolBar_search = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar_search);

    //toolBar_edit->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    //toolBar_edit->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    toolBar_edit->setWindowTitle("search");

    QLabel* lbl_DB_caption = new QLabel("库:");
    toolBar_search->addWidget(lbl_DB_caption);
    QComboBox* cB_lib = new QComboBox();
    cB_lib->setFocusPolicy(Qt::NoFocus);
    toolBar_search->addWidget(cB_lib);

    QLabel* lbl_search_caption = new QLabel("搜索：");
    toolBar_search->addWidget(lbl_search_caption);

    QLineEdit* lE_search = new QLineEdit();
    lE_search->setMaximumWidth(200);
    toolBar_search->addWidget(lE_search);

    // dW_DB
    QDockWidget* dW_DB = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, dW_DB);
    dW_DB->setWindowTitle("数据库");
    
    QListWidget* lW_DB = new QListWidget();
   
    QGridLayout* layout_dW_DB_Grid = new QGridLayout(dW_DB);
    layout_dW_DB_Grid->setContentsMargins(0, 0, 0, 0);
    layout_dW_DB_Grid->addWidget(lW_DB);
    QWidget* widget_dW_DB = new QWidget();

    widget_dW_DB->setLayout(layout_dW_DB_Grid);
    
    dW_DB->setWidget(widget_dW_DB);

    
    statusBar()->showMessage("界面布局完成！",1000);
}
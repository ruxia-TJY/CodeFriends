#include "CodeFriends.h"

CodeFriends::CodeFriends(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    this->resize(QSize(2000, 1000));
    
    db = new Database();
    QFileInfo dbfile("db_codefriends.db");
    
    if (!dbfile.isFile()) {
        db->createDB();
    }
    
    db->openDB();
    uiabout = new UiAbout();

    setupEditor();
    setupUI();
    setupLibrary();
}

CodeFriends::~CodeFriends()
{}

void CodeFriends::closeEvent(QCloseEvent* event)
{
    //int result = QMessageBox::information(this, tr("提示"), tr("当前未保存，继续将丢失更改！"),
    //    tr("继续"), tr("取消"), 0, 1);
    //if (1 == result) {
    //    event->ignore();
    //}

    uiabout->close();
    
}

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
    statusBar()->showMessage(tr("加载界面..."), 1000);
    // toolBar_edit
    QToolBar* toolBar_edit = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar_edit);

    toolBar_edit->setWindowTitle(tr("编辑"));
    
    QAction* pb_add = new QAction(QIcon(":/icon/resource/PNG_add.png"), tr("添加"), this);
    pb_add->setToolTip(tr("添加"));
    QAction* pb_save = new QAction(QIcon(":/icon/resource/PNG_save.png"), tr("保存"), this);
    pb_save->setToolTip(tr("保存"));
    QAction* pb_delete = new QAction(QIcon(":/icon/resource/PNG_delete.png"), tr("删除"), this);
    pb_delete->setToolTip(tr("删除"));
    QAction* pb_refresh = new QAction(QIcon(":/icon/resource/PNG_refresh.png"), tr("刷新"), this);
    pb_refresh->setToolTip(tr("刷新"));
    
    toolBar_edit->addAction(pb_add);
    toolBar_edit->addAction(pb_save);
    toolBar_edit->addAction(pb_delete);
    toolBar_edit->addAction(pb_refresh);

    connect(pb_add, &QAction::triggered, this, &CodeFriends::add_code);
    connect(pb_save, &QAction::triggered, this, &CodeFriends::save_code);
    connect(pb_delete, &QAction::triggered, this, &CodeFriends::delete_code);
    connect(pb_refresh, &QAction::triggered, this, &CodeFriends::refresh_code);

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar_edit->addWidget(spacer);

    QAction* pb_attachment_import = new QAction(tr("导入附件"), this);
    QAction* pb_attachment_export = new QAction(tr("导出附件"), this);

    QMenu* pb_attachment_menu = new QMenu(tr("附件"));
    pb_attachment_menu->addAction(pb_attachment_import);
    pb_attachment_menu->addAction(pb_attachment_export);
    
    QToolButton* pb_attachment_btn = new QToolButton();
    pb_attachment_btn->setIcon(QIcon(":/icon/resource/PNG_attachment.png"));
    pb_attachment_btn->setPopupMode(QToolButton::InstantPopup);
    pb_attachment_btn->setMenu(pb_attachment_menu);
    
    toolBar_edit->addWidget(pb_attachment_btn);

    QAction* pb_about = new QAction(tr("关于"), this);
    QAction* pb_setting = new QAction(QIcon(":/icon/resource/PNG_setting.png"),tr("设置"), this);

    QMenu* pb_help_menu = new QMenu(tr("帮助"));
    pb_help_menu->addAction(pb_setting);
    pb_help_menu->addSeparator();
    pb_help_menu->addAction(pb_about);

    QToolButton* pb_help_btn = new QToolButton();
    pb_help_btn->setIcon(QIcon(":/icon/resource/PNG_help.png"));
    pb_help_btn->setPopupMode(QToolButton::InstantPopup);
    pb_help_btn->setMenu(pb_help_menu);

    toolBar_edit->addWidget(pb_help_btn);
    
    connect(pb_about, &QAction::triggered, this, &CodeFriends::show_ui_about);

    this->addToolBarBreak();

    // toolBar_search
    QToolBar* toolBar_search = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar_search);

    toolBar_search->setWindowTitle(tr("搜索"));

    QLabel* lbl_DB_caption = new QLabel(tr("库"));
    toolBar_search->addWidget(lbl_DB_caption);

    cB_lib = new QComboBox;
    cB_lib->setFocusPolicy(Qt::NoFocus);
    toolBar_search->addWidget(cB_lib);
    

    QLabel* lbl_search_caption = new QLabel(tr("搜索："));
    toolBar_search->addWidget(lbl_search_caption);

    lE_search = new QLineEdit;
    lE_search->setMaximumWidth(200);
    toolBar_search->addWidget(lE_search);

    // dW_DB
    QDockWidget* dW_DB = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, dW_DB);
    dW_DB->setWindowTitle(tr("数据库"));
    
    lW_DB = new QListWidget;
   
    QGridLayout* layout_dW_DB_Grid = new QGridLayout(dW_DB);
    layout_dW_DB_Grid->setContentsMargins(0, 0, 0, 0);
    layout_dW_DB_Grid->addWidget(lW_DB);
    QWidget* widget_dW_DB = new QWidget();

    widget_dW_DB->setLayout(layout_dW_DB_Grid);
    
    dW_DB->setWidget(widget_dW_DB);

    
    statusBar()->showMessage("界面布局完成！",1000);

    // editor and titleline
    titleline = new QLineEdit;
    QWidget* widget_editor = new QWidget();
    QVBoxLayout* vboxlayout = new QVBoxLayout(widget_editor);
    vboxlayout->setMargin(0);
    vboxlayout->addWidget(titleline);
    vboxlayout->addWidget(editor);
    widget_editor->setLayout(vboxlayout);
    setCentralWidget(widget_editor);
}

void CodeFriends::setupLibrary()
{
    cB_lib->clear();
    QStringList lst = db->getLibraryList();
    cB_lib->addItems(lst);
}

void CodeFriends::save_code()
{
    if (0 == titleline->text().length()) {
        QMessageBox::warning(this, tr("警告"), tr("请设置一个标题！"));
        return;
    }

    // check title in db   
    QString title = titleline->text();
    int mode = db->isCodeTitleExist(title);
    QString code = editor->toPlainText();
    QDateTime current_datetime = QDateTime::currentDateTime();

    QString updateDateTime = current_datetime.toString("yyyy-mm-dd hh:mm:ss");
    

    if (mode >= 1) {
        // 数据库中存在，修改
        //QMessageBox::warning(this, tr("警告"), tr("当前标题已存在！请重新设置！"));

    }
    else {
        // 数据库中不存在，添加
        cfcode data = {
            title,
            code,
            updateDateTime,
            updateDateTime,
            
        };
        //db->createCode(data);
    }
    
   


}

void CodeFriends::delete_code()
{
}

void CodeFriends::refresh_code()
{
}

void CodeFriends::show_ui_about()
{
    uiabout->show();
}

void CodeFriends::add_code()
{
    //QMessageBox::information(this, "test", "add");
}


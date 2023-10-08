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
    uisetting = new UiSetting();

    setupEditor();
    setupUI();

    timer = new QTimer;
    current_datetime = new QDateTime;
    connect(timer, &QTimer::timeout, this, &CodeFriends::timeUpdate);
    timer->start(1000);

    setupLibrary();
    setupTitleList();
    if (lW_DB->count() > 0)lW_DB->setCurrentRow(0);
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
    uisetting->close();
    
}

void CodeFriends::setupEditor()
{
    editor = new CodeEditor;

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
    pb_add->setToolTip(tr("添加 （Ctrl + N)"));
    pb_add->setStatusTip(tr("添加 (Ctrl + N)"));
    pb_add->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    QAction* pb_save = new QAction(QIcon(":/icon/resource/PNG_save.png"), tr("保存"), this);
    pb_save->setToolTip(tr("保存 (Ctrl + S)"));
    pb_save->setStatusTip(tr("保存 (Ctrl + S)"));
    pb_save->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    QAction* pb_delete = new QAction(QIcon(":/icon/resource/PNG_delete.png"), tr("删除"), this);
    pb_delete->setToolTip(tr("删除 (delete)"));
    pb_delete->setStatusTip(tr("删除 (delete)"));
    pb_delete->setShortcut(QKeySequence(Qt::Key_Delete));
    QAction* pb_refresh = new QAction(QIcon(":/icon/resource/PNG_refresh.png"), tr("刷新"), this);
    pb_refresh->setToolTip(tr("刷新 (F5)"));
    pb_refresh->setStatusTip(tr("刷新 (F5)"));
    pb_refresh->setShortcut(QKeySequence(Qt::Key_F5));
    
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
    connect(pb_setting, &QAction::triggered, this, &CodeFriends::show_ui_setting);

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
    
    connect(lE_search, &QLineEdit::textChanged, this, &CodeFriends::search_title);


    toolBar_search->addWidget(lE_search);

    // dW_DB
    QDockWidget* dW_DB = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, dW_DB);
    dW_DB->setWindowTitle(tr("数据库"));
    
    lW_DB = new QListWidget;
    lbl_title_list_count = new QLabel;
    lbl_title_list_count->setText("Count:0");
    
    QGridLayout* layout_dW_DB_Grid = new QGridLayout(dW_DB);
    layout_dW_DB_Grid->setContentsMargins(0, 0, 0, 0);
    layout_dW_DB_Grid->addWidget(lW_DB);
    layout_dW_DB_Grid->addWidget(lbl_title_list_count);
    QWidget* widget_dW_DB = new QWidget();

    widget_dW_DB->setLayout(layout_dW_DB_Grid);
    
    dW_DB->setWidget(widget_dW_DB);

    connect(lW_DB, &QListWidget::currentItemChanged, this, &CodeFriends::readCodeData);
    statusBar()->showMessage("界面布局完成！",1000);

    // editor and titleline
    lE_title = new QLineEdit;
    QWidget* widget_editor = new QWidget();
    QVBoxLayout* vboxlayout = new QVBoxLayout(widget_editor);
    vboxlayout->setMargin(0);
    vboxlayout->addWidget(lE_title);
    vboxlayout->addWidget(editor);
    widget_editor->setLayout(vboxlayout);
    setCentralWidget(widget_editor);


    // statusBar
    lbl_current_datetime = new QLabel;
    lbl_create_datetime = new QLabel;
    lbl_update_datetime = new QLabel;
    lbl_attachment_info = new QLabel;
    
    statusBar()->addPermanentWidget(lbl_create_datetime);
    statusBar()->addPermanentWidget(lbl_update_datetime);
    statusBar()->addPermanentWidget(lbl_attachment_info);
    statusBar()->addPermanentWidget(lbl_current_datetime);

}

void CodeFriends::setupLibrary()
{
    cB_lib->clear();
    QStringList lst = db->getLibraryList();
    cB_lib->addItems(lst);
}

void CodeFriends::setupTitleList()
{
    lW_DB->clear();
    QString library = cB_lib->currentText();
    QStringList lst = db->getTitleListInLibrary(library);
    lW_DB->addItems(lst);
    lW_DB->sortItems(Qt::AscendingOrder);

    QString count = QString("Count:%1").arg(lst.size());
    lbl_title_list_count->setText(count);
    
}

void CodeFriends::timeUpdate()
{
    current_datetime = &QDateTime::currentDateTime();
    QString str_current_datetime = current_datetime->toString("yyyy-MM-dd HH:mm:ss");
    lbl_current_datetime->setText(str_current_datetime);
}

void CodeFriends::save_code()
{
    if (0 == lE_title->text().length()) {
        QMessageBox::warning(this, tr("警告"), tr("请设置一个标题！"));
        return;
    }

    // check title exist in db   
    QString library = cB_lib->currentText();
    QString title = lE_title->text();
    int mode = db->isCodeTitleExist(title,library);

    QString code = editor->toPlainText();
    QDateTime curDateTime = QDateTime::currentDateTime();
    QString updateDateTime = curDateTime.toString("yyyy-MM-dd HH:mm:ss");

    if (mode >= 1) {
        // if exist in database, update
        editor_changed_mode = false;

        cfcode data = {
            title,
            code,
            updateDateTime,
            updateDateTime,
            library,
        };
        if (db->updateCodeData(title, library, data)) {
            QMessageBox::information(this, tr("提示"), tr("修改成功！"));
            //refresh
            lbl_update_datetime->setText(QString("Update:%1").arg(updateDateTime));
        }
    }
    else {
        
        // not exist, add
        cfcode data = {
            title,
            code,
            updateDateTime,
            updateDateTime,
            library,
        };
        if (db->createCode(data)) {
            QMessageBox::information(this, tr("提示"), tr("数据添加成功！"));
            // refresh list
            setupTitleList();
            editor_changed_mode = false;

            QList<QListWidgetItem*>match = lW_DB->findItems(title, Qt::MatchExactly);
            lW_DB->setCurrentItem(match[0]);
        }
        else {
            QMessageBox::warning(this, tr("提示"), tr("数据添加失败！"));
        }
    }
}

void CodeFriends::delete_code()
{
    if (lW_DB->currentIndex().row() < 0) return;
    
    QString title = lW_DB->currentItem()->text();
    QString library = cB_lib->currentText();
    
    int result = QMessageBox::information(this, tr("提示"), tr("确定要删除代码吗？"),
        tr("确定"), tr("取消"), 0, 1);
    if (1 == result)return;

    if (db->deleteCodeData(title, library)){
        QMessageBox::information(this, tr("提示"), tr("删除成功！"));
        
        setupTitleList();
    }
    else {
        QMessageBox::warning(this, tr("Error"), tr("删除失败！"));
    }
}

void CodeFriends::refresh_code()
{
    setupLibrary();
    setupTitleList();
    if (lW_DB->count() > 1)lW_DB->setCurrentRow(0);
}

void CodeFriends::show_ui_about()
{
    uiabout->show();
}

void CodeFriends::readCodeData()
{
    if (lW_DB->currentIndex().row() < 0)return;

    QString title = lW_DB->currentItem()->text();
    QString library = cB_lib->currentText();
    cfcode code = db->queryCodeData(title, library);
    
    lE_title->setText(code.title);
    editor->setPlainText(code.code);
    lbl_create_datetime->setText(QString("Create:%1").arg(code.createDateTime));
    lbl_update_datetime->setText(QString("Update:%1").arg(code.updateDateTime));

    if (db->isCodeDataHasAttachment(title, library)) {
        lbl_attachment_info->setText(QString("Attachment:有"));
    }
    else {
        lbl_attachment_info->setText(QString("Attachment:无"));
    }
    
}

void CodeFriends::search_title()
{
    QString search_target = lE_search->text();
    QString search_target_wildcard;
    search_target_wildcard.clear();
    search_target_wildcard.push_back('*');
    for (int i = 0; i < (int)search_target.size(); i++) {
        search_target_wildcard.push_back(search_target[i]);
        search_target_wildcard.push_back('*');
    }
    QList<QListWidgetItem*>match = lW_DB->findItems(search_target_wildcard, Qt::MatchWildcard);
    
    for (int i = 0; i < lW_DB->count(); i++)lW_DB->item(i)->setHidden(true);
    
    for (int i = 0; i < (int)match.size(); i++) match[i]->setHidden(false);
}

void CodeFriends::show_ui_setting()
{
    uisetting->show();
}

void CodeFriends::add_code()
{
    lE_title->clear();
    editor->clear();
    lE_title->setFocus();
    editor_changed_mode = true;
}


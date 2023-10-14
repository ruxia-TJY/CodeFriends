// TODO UiSetting界面和逻辑
#include "UiSetting.h"

UiSetting::UiSetting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("设置"));

	db = new Database;
	db->openDB();

	resize(1000, 800);

	setupTab();

	getlibrary();
}

UiSetting::~UiSetting()
{}

void UiSetting::setupTab()
{
	tabWid = new QTabWidget;
	QGridLayout* gridlayout = new QGridLayout;
	gridlayout->setContentsMargins(0,0,0,0);
	gridlayout->addWidget(tabWid);

	this->setLayout(gridlayout);

	// tab_general
	tab_general = new QWidget;
	


	// tab_library
	tab_library = new QWidget;
	QGridLayout* gridlayout_library = new QGridLayout;
	tab_library->setLayout(gridlayout_library);

	cB_library_defaultlibrary = new QComboBox();
	
	QLabel* lbl_library = new QLabel("Current Library");
	
	QPushButton* pb_delete = new QPushButton("delete");
	connect(pb_delete, &QPushButton::clicked, this, &UiSetting::deleteLibrary);
	QPushButton* pb_add = new QPushButton("create new");
	connect(pb_add, &QPushButton::clicked, this, &UiSetting::addLibrary);

	gridlayout_library->addWidget(lbl_library,0,0);
	gridlayout_library->addWidget(cB_library_defaultlibrary, 0, 1);
	gridlayout_library->addWidget(pb_delete, 0, 2);
	gridlayout_library->addWidget(pb_add, 1, 2);
	
	

	tabWid->addTab(tab_library, "Library");

}

void UiSetting::getlibrary()
{
	cB_library_defaultlibrary->clear();
	cB_library_defaultlibrary->addItems(db->getLibraryList());
}

void UiSetting::addLibrary()
{
	bool ret = false;
	QString name = QInputDialog::getText(this, "CodeFriends",
		"Library Name:",QLineEdit::Normal,"",&ret);

	
	if (!ret)return;

	if (name.isEmpty()) {
		QMessageBox::information(this, "Error", "Fail: input cannot be empty!");
		return;
	}

	if (db->isLibraryExist(name)) {
		QMessageBox::information(this, "Error", "Fail: Library " + name + " exist!");
		return;
	}

	if (!db->createLibrary(name, "")) {
		QMessageBox::information(this, "Error", "Fail: create error!");
		return;
	}

	emit refreshParentLibrary();
	getlibrary();
}

void UiSetting::deleteLibrary()
{
	if (1 == cB_library_defaultlibrary->count()) {
		QMessageBox::warning(this, "Error", "Fail: the last library,cannot be delete!");
		return;
	}

	QString name = cB_library_defaultlibrary->currentText();
	if (db->getTitleCount(name)) {
		int ret = QMessageBox::warning(this, "Error", "Fail: has data in Library " + name + " ,Sure delete?",
			"确定", "取消", 0, 1);
		if (ret)return;
	}

	if (!db->deleteLibrary(name)) {
		QMessageBox::warning(this, "Error", "Fail: delete failed!");
		return;
	};

	QMessageBox::information(this, "CodeFriends", "Delete successful!");

	emit refreshParentLibrary();
	getlibrary();
}



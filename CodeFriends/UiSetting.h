#ifndef QT_UI_SETTING_H
#define QT_UI_SETTING_H

#include <QWidget>
#include <qtabwidget.h>
#include <qgridlayout.h>
#include <qobject.h>
#include <qlistwidget.h>
#include <qlabel.h>
#include <qstringlistmodel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qinputdialog.h>
#include <qmessagebox.h>
#include "ui_Setting.h"
#include "database.h"

QT_BEGIN_NAMESPACE
class QObject;

QT_END_NAMESPACE

class UiSetting : public QWidget
{
	Q_OBJECT

public:
	UiSetting(QWidget* parent = nullptr);
	~UiSetting();

public slots:

private:
	Ui::UiSettingClass ui;
	void setupTab();
	void getlibrary();

	Database* db;

	QTabWidget* tabWid;
	QWidget* tab_library;
	QWidget* tab_general;

	QComboBox* cB_library_defaultlibrary;

	void addLibrary();
	void deleteLibrary();
	
private slots:
	

signals:
	void refreshParentLibrary();
};

#endif // !QT_UI_SETTING_H
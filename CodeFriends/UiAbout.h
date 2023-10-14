#ifndef QT_UI_ABOUT_H
#define QT_UI_ABOUT_H

#include <QWidget>
#include <qlabel.h>
#include <qgridlayout.h>
#include "ui_About.h"
#include "constant.h"

class UiAbout : public QWidget
{
	Q_OBJECT

public:
	UiAbout(QWidget* parent = nullptr);
	~UiAbout();

private:
	Ui::UiAboutClass ui;
	QLabel* lbl_about;
};
#endif // !QT_UI_ABOUT_H
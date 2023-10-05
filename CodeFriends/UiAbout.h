#pragma once

#include <QWidget>
#include <qlabel.h>
#include <qgridlayout.h>
#include "ui_About.h"
#include "constant.h"

class UiAbout : public QWidget
{
	Q_OBJECT

public:
	UiAbout(QWidget *parent = nullptr);
	~UiAbout();

private:
	Ui::UiAboutClass ui;
	QLabel* lbl_about;
};

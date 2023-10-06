#pragma once

#include <QWidget>
#include "ui_Setting.h"

class UiSetting : public QWidget
{
	Q_OBJECT

public:
	UiSetting(QWidget *parent = nullptr);
	~UiSetting();

private:
	Ui::UiSettingClass ui;
};

// TODO UiSetting界面和逻辑
#include "UiSetting.h"

UiSetting::UiSetting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("设置"));
}

UiSetting::~UiSetting()
{}

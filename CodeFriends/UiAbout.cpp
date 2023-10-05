#include "UiAbout.h"

UiAbout::UiAbout(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	this->setWindowTitle(tr("关于"));
	lbl_about = new QLabel();
	lbl_about->setAlignment(Qt::AlignCenter);
	
	lbl_about->setText("CodeFriends" "\n" VERSION "\n\u00A9 2023" AUTHOR_AND_EMAIL);

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(lbl_about);
	
	this->setLayout(layout);
}

UiAbout::~UiAbout()
{}

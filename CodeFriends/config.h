#ifndef CONFIG_H
#define CONFIG_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>
#include <qfont.h>
#include <qcoreapplication.h>
#include <qdir.h>

class Config
{
public:
	Config();
	bool isConfigFileExist();
	QString getConfigFilePath();

	void createDefaultConfigFile();
	bool loadConfigFile();
	
	QFont Font_default;
	QFont Font_editor;
	
private:
	bool configFileExist = false;
	QString configFilePath;


	void toJson();
};


#endif // !CONFIG_H
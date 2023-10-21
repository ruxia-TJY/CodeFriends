#include "config.h"

/*
{
	"ui":{
		"default":{
			"font":{
				"family":"Simsun",
				"size":10
			}
		},
		"MenuBar":{
			"font":{
				"family":"Simsun",
				"size":10
			}
		},
		"StatusBar":{
			"font":{
				"family":"Simsun",
				"size":10
			}
		},
		"Editor":{
			"font":{
				"family":"Simsun",
				"size":10
			}
		}
	}
	"library":{
		"default":"C",
		
	}
}
*/
Config::Config()
{
	QString dirPath = QCoreApplication::applicationDirPath();
	QString fileName("config.json");
	QDir dir(dirPath);
	configFilePath = dir.absoluteFilePath(fileName);

	if (!isConfigFileExist())createDefaultConfigFile();
	loadConfigFile();
}

bool Config::isConfigFileExist()
{
	QFile configFile(configFilePath);
	if (false == configFile.exists())
	{
		configFileExist = false;
		return false;
	}

	configFileExist = true;
	return true;
}

QString Config::getConfigFilePath()
{
	return configFilePath;
}

void Config::createDefaultConfigFile()
{
	QFile configFile(configFilePath);
	if (!configFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}
	QTextStream txt(&configFile);
	QString json = "{\n"
		"	\"ui\":{\n"
		"       \"default\":{\n"
		"           \"font\":{\n"
		"               \"family\":\"Simsun\",\n"
		"               \"size\":10\n"
		"           }\n"
		"       },\n"
		"		\"Editor\":{\n"
		"			\"font\":{\n"
		"				\"family\":\"Simsun\",\n"
		"				\"size\" : 10\n"
		"			}\n"
		"		}\n"
		"	},\n"
		"	\"library\":{\n"
		"		\"default\":\"C\"\n"
		"	}\n"
		"}";
	txt << json.toUtf8() << endl;
	configFile.close();
}

bool Config::loadConfigFile()
{
	QFile configFile(configFilePath);
	if (!configFileExist) return false;

	if (false == configFile.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

	QString config = configFile.readAll();
	configFile.close();

	QJsonParseError err;
	QJsonDocument document = QJsonDocument::fromJson(config.toUtf8(), &err);
	if (err.error != QJsonParseError::NoError) return false;

	QJsonObject root_obj = document.object();
	
	QJsonObject json_ui = root_obj.find("ui").value().toObject();

	QJsonObject json_ui_default = json_ui.find("default").value().toObject();
	QJsonObject json_ui_default_font = json_ui_default.find("font").value().toObject();
	Font_default.setFamily(json_ui_default_font.find("family").value().toString());
	Font_default.setPointSize(json_ui_default_font.find("size").value().toInt());
	
	QJsonObject json_ui_editor = json_ui.find("Editor").value().toObject();
	QJsonObject json_ui_editor_font = json_ui_editor.find("font").value().toObject();
	Font_editor.setFamily(json_ui_editor_font.find("family").value().toString());
	Font_editor.setPointSize(json_ui_editor_font.find("size").value().toInt());
	
	
	return true;
}



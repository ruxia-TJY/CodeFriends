#ifndef DATABASE_H
#define DATABASE_H

#include <qsqldatabase.h>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <qstringlist.h>
#include "constant.h"

typedef struct {
	QString title;
	QString code;
	QString createDateTime;
	QString updateDateTime;
	QString library;
	QByteArray attachment;

}cfcode;

class Database
{
public:
	Database();
	~Database();

	bool createDB();
	bool openDB();
	void closeDB();

	void createTable();
	bool createLibrary(QString name,QString description);
	QStringList getLibraryList();

	bool createCode(cfcode &cfcodedb);
	bool createCode(QString title, QString code);
	
	int isCodeTitleExist(QString title);
	bool isTableExist(QString& tableName);
private:
	QSqlDatabase database;

};

#endif
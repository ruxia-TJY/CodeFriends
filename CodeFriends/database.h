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

	bool createDB();											// create Database file
	bool openDB();												// open Database
	void closeDB();												// close Database

	bool createTable_Library();									// create TABLE_LIBRARY
	
	bool isLibraryExist(QString name);							// is library name in TABLE_LIBRARY
	bool createLibrary(QString name, QString description);		// add library to TABLE_LIBRARY and create TABLE_CODE_name
	bool deleteLibrary(QString name);							// delete library name in TABLE_LIBRARY and delete TABLE_CODE_name

	cfcode queryCodeData(QString title, QString library);
	bool deleteCodeData(QString title, QString library);
	bool updateCodeData(QString title,QString library, cfcode& db);

	QStringList getLibraryList();

	QStringList getTitleListInLibrary(QString library);

	int getTitleCount(QString library);


	bool createCode(cfcode &cfcodedb);
	bool createCode(QString title, QString code,QString createDateTime,QString updateTime,QString library);
	
	int isCodeTitleExist(QString title,QString library);
	


	bool isCodeDataHasAttachment(QString title, QString library);
private:
	QSqlDatabase database;


	bool createTable(QString name);								// create TABLE_CODE_name
	bool isTableExist(QString& tableName);
};

#endif
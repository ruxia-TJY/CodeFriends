#include "database.h"


Database::Database()
{
	if (QSqlDatabase::contains("db_codefriends")) {
		database = QSqlDatabase::database("db_codefriends");
	}
	else {
		database = QSqlDatabase::addDatabase("QSQLITE");
		database.setDatabaseName("db_codefriends.db");
	}
}

Database::~Database()
{
	database.close();
}

bool Database::createDB()
{
	// create Database file
	if(!openDB())return false;
	// create TABLE_LIBRARY 
	// the list for library;
	if(!createTableLibrary())return false;
	// create Default code table;
	// default: TABLE_CODE_C
	if (!createLibrary("C","code of C language")) return false;
	return true;
}

bool Database::openDB()
{
	if (!database.open()) return false;
	return true;
}

void Database::closeDB()
{
	database.close();
}

bool Database::createTableLibrary()
{
	QSqlQuery sqlQuery;
	QString sql = QString("CREATE TABLE TABLE_LIBRARY (\
		name TEXT NOT NULL,\
		description TEXT NOT NULL)");
	
	sqlQuery.prepare(sql);
	
	if (!sqlQuery.exec())return false;

	return true;
}

bool Database::createTable(QString name)
{
	QSqlQuery sqlQuery;
	QString sql = QString("CREATE TABLE TABLE_CODE_%1 (\
		title TEXT NOT NULL,\
		code TEXT NOT NULL,\
		createDateTime TEXT NOT NULL,\
		updateDateTime TEXT NOT NULL,\
		attachment BLOB)").arg(name);

	sqlQuery.prepare(sql);

	if (!sqlQuery.exec())return false;

	return true;
}

bool Database::isLibraryExist(QString name)
{
	QSqlQuery sqlQuery;
	/*QString sql = QString("SELECT name FROM TABLE_LIBRARY WHERE name = \"%1\"")
		.arg(name);*/

	sqlQuery.prepare("SELECT name FROM TABLE_LIBRARY WHERE name = :name");
	sqlQuery.bindValue(":name", name);

	if (!sqlQuery.exec())return false;
	sqlQuery.last();
	int count = sqlQuery.at() + 1;

	return (count > 0) ? true : false;
}

bool Database::createLibrary(QString name, QString description)
{
	if (isLibraryExist(name))return false;

	QSqlQuery sqlQuery;
	sqlQuery.prepare("INSERT INTO TABLE_LIBRARY VALUES(:name,:description)");
	sqlQuery.bindValue(":name", name);
	sqlQuery.bindValue(":description", description);

	if (!sqlQuery.exec()) return false;
	
	if (!createTable(name)) return false;
	
	return true;
}

bool Database::deleteLibrary(QString name)
{
	QString sql = QString("DROP TABLE TABLE_CODE_%1").arg(name);

	QSqlQuery sqlQuery;
	sqlQuery.prepare(sql);

	if (!sqlQuery.exec()) return false;

	return true;
}

cfcode Database::queryCodeData(QString title, QString library)
{
	cfcode db;

	QSqlQuery sqlQuery;
	sqlQuery.prepare("SELECT * FROM TABLE_CODE_" + library + " WHERE title=:title");
	sqlQuery.bindValue(":title", title);

	if (!sqlQuery.exec()) {
		QMessageBox::warning(nullptr, "Error", "Fail: Could not query Database");
		return db;
	}
	else {
		sqlQuery.next();
		db.title = sqlQuery.value(0).toString();
		db.code = sqlQuery.value(1).toString();
		db.createDateTime = sqlQuery.value(2).toString();
		db.updateDateTime = sqlQuery.value(3).toString();
	}

	return db;
}

bool Database::deleteCodeData(QString title, QString library)
{
	QSqlQuery sqlQuery;

	sqlQuery.prepare("DELETE FROM TABLE_CODE_" + library + " WHERE title = :title");
	sqlQuery.bindValue(":title", title);
	if (!sqlQuery.exec())return false;
	return true;
}

QStringList Database::getLibraryList()
{
	QStringList lst;
	QSqlQuery sqlQuery;
	sqlQuery.exec("SELECT * FROM TABLE_LIBRARY");
	if (!sqlQuery.exec()) {
		QMessageBox::warning(nullptr, "Error", "Fail to query DATABASE");
	}
	else {
		while (sqlQuery.next()) {
			QString name = sqlQuery.value(0).toString();
			lst << name;
		}
	}
	return lst;
}

QStringList Database::getTitleListInLibrary(QString library)
{
	QStringList lst;
	QSqlQuery sqlQuery;

	sqlQuery.prepare("SELECT title FROM TABLE_CODE_" + library);
	if (!sqlQuery.exec()) {
		QMessageBox::warning(nullptr, "Error", "Fail to query DATABASE");
	}
	else {
		while (sqlQuery.next()) {
			QString name = sqlQuery.value(0).toString();
			lst << name;
		}
	}
	return lst;
}

bool Database::createCode(cfcode& cfcodedb)
{
	QSqlQuery sqlQuery;

	sqlQuery.prepare("INSERT INTO TABLE_CODE_" +  cfcodedb.library + " VALUES(:title,:code,:create,:update,NULL)");	
	sqlQuery.bindValue(":title", cfcodedb.title);
	sqlQuery.bindValue(":code", cfcodedb.code);
	sqlQuery.bindValue(":create", cfcodedb.createDateTime);
	sqlQuery.bindValue(":update", cfcodedb.updateDateTime);
	
	if (!sqlQuery.exec()) {
		qDebug() << sqlQuery.lastError();
		QMessageBox::warning(nullptr, "Error", "Fail to insert data.");
		return false;
	}
	return true;
}

bool Database::createCode(QString title, QString code, QString createDateTime, QString updateTime, QString library)
{
	return false;
}

int Database::isCodeTitleExist(QString title,QString library)
{
	QSqlQuery sqlQuery;
	
	sqlQuery.prepare("SELECT title FROM TABLE_CODE_" + library + " WHERE title=:title");
	sqlQuery.bindValue(":title", title);

	if (!sqlQuery.exec()){
		return -1;
	}

	sqlQuery.last();
	int count = sqlQuery.at() + 1;

	return count;
}

bool Database::isTableExist(QString& tableName)
{
	QSqlDatabase database = QSqlDatabase::database();
	if (database.tables().contains(tableName))return true;
	
	return false;
}
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
}

bool Database::createDB()
{
	openDB();
	createTable();
	return true;
}

bool Database::openDB()
{
	if (!database.open()) {

		QMessageBox::warning(nullptr,"error",
								database.lastError().text());		
		return false;
	}
	else
	{

	}
	return true;
}

void Database::closeDB()
{
	database.close();
}

void Database::createTable()
{
	QSqlQuery sqlQuery;
	QString createsql = QString("CREATE TABLE TABLE_CODE (\
		title TEXT NOT NULL,\
		code TEXT NOT NULL,\
		createDateTime TEXT NOT NULL,\
		updateDateTime TEXT NOT NULL,\
		library TEXT NOT NULL,\
		attachment BLOB)");
	QString createsql2 = QString("CREATE TABLE TABLE_LIBRARY (\
		name TEXT NOT NULL,\
		description TEXT NOT NULL)");
	sqlQuery.prepare(createsql);
	if (!sqlQuery.exec()) {
		QMessageBox::warning(nullptr, "Error", "Failed to create Table");
	}

	sqlQuery.prepare(createsql2);
	if (!sqlQuery.exec()) {
		QMessageBox::warning(nullptr, "Error", "Failed to create Table");
	}
}

bool Database::createLibrary(QString name, QString description)
{
	QSqlQuery sqlQuery;
	sqlQuery.prepare("INSERT INTO TABLE_LIBRARY VALUES(:name,:description)");
	sqlQuery.bindValue(":name", name);
	sqlQuery.bindValue(":description", description);

	if (!sqlQuery.exec()) {
		QMessageBox::warning(nullptr, "Error", "Fail to insert library.");
		return false;
	}
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

bool Database::createCode(cfcode& cfcodedb)
{
	QSqlQuery sqlQuery;
	sqlQuery.prepare("INSERT INTO TABLE_CODE VALUES(:title,:code,:createDateTime,:updateDateTime,:library)");
	sqlQuery.bindValue(":title", cfcodedb.title);
	sqlQuery.bindValue(":code", cfcodedb.code);
	sqlQuery.bindValue(":createDateTime", cfcodedb.createDateTime);
	sqlQuery.bindValue(":updateDateTime", cfcodedb.updateDateTime);
	sqlQuery.bindValue(":library", cfcodedb.library);
	if (!sqlQuery.exec()) {
		QMessageBox::warning(nullptr, "Error", "Fail to insert data.");
		return false;
	}
	return true;
}

bool Database::createCode(QString title, QString code)
{
	return false;
}

int Database::isCodeTitleExist(QString title)
{
	QSqlQuery sqlQuery;
	QString sql = QString("SELECT title FROM TABLE_CODE WHERE title='%1'").arg(title);
	if (!sqlQuery.exec(sql)){
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
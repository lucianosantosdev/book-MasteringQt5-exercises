#include "DatabaseManager.h"

#include <QSqlDatabase>

DatabaseManager&
DatabaseManager::instance()
{
  static DatabaseManager singleton;
  return singleton;
}

DatabaseManager::~DatabaseManager()
{
  mDatabase->close();
  delete mDatabase;
}

const AlbumDao&
DatabaseManager::albumDao()
{
  return *mAlbumDao;
}

DatabaseManager::DatabaseManager(const QString& path)
  : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
{
  mAlbumDao = new AlbumDao(*mDatabase);
  mDatabase->setDatabaseName(path);
  mDatabase->open();
  mAlbumDao->init();
}

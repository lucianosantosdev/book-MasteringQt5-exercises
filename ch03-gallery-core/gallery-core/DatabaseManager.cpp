#include "DatabaseManager.h"
#include "AlbumDao.h"
#include "PictureDao.h"

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

const PictureDao&
DatabaseManager::pictureDao() const
{
  return *mPictureDao;
}

DatabaseManager::DatabaseManager(const QString& path)
  : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
{
  mAlbumDao = new AlbumDao(*mDatabase);
  mPictureDao = new PictureDao(*mDatabase);
  mDatabase->setDatabaseName(path);
  mDatabase->open();
  mAlbumDao->init();
  mPictureDao->init();
}

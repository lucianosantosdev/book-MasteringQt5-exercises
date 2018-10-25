#pragma once

#include "AlbumDao.h"
#include "PictureDao.h"

#include <QString>

class QSqlDatabase;

const QString DATABASE_FILENAME = "gallery.db";

class DatabaseManager
{
public:
  static DatabaseManager& instance();
  ~DatabaseManager();

  const AlbumDao& albumDao();

  const PictureDao& pictureDao() const;

protected:
  DatabaseManager(const QString& path = DATABASE_FILENAME);
  DatabaseManager(const DatabaseManager& rhs);
  DatabaseManager& operator=(const DatabaseManager& rhs);

private:
  QSqlDatabase* mDatabase;
  AlbumDao* mAlbumDao;
  PictureDao* mPictureDao;
};

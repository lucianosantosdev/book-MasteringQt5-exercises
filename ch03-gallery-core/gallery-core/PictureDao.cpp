#include "PictureDao.h"
#include "Album.h"
#include "Picture.h"

#include <memory>
#include <vector>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QtDebug>

PictureDao::PictureDao(QSqlDatabase& database)
  : mDatabase(database)
{}

void
PictureDao::init() const
{
  if (!mDatabase.tables().contains("pictures")) {
    QSqlQuery query(mDatabase);
    bool ok = query.exec("CREATE TABLE pictures ("
                         "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "  album_id INTEGER,"
                         "  url TEXT"
                         ")");
    if (!ok) {
      qCritical() << "Database ERROR: Failed creating table pictures";
    }
  }
}

void
PictureDao::insert(const int& albumId, Picture& picture) const
{
  QSqlQuery query(mDatabase);

  query.prepare("INSERT INTO pictures (album_id, url) VALUES (:albumId, :url)");
  query.bindValue(":albumId", albumId);
  query.bindValue(":url", picture.fileUrl());

  bool ok = query.exec();
  if (!ok) {
    qCritical() << "Failed inserting into pictures";
  }

  picture.setAlbumId(albumId);
  picture.setId(query.lastInsertId().toInt());
}

void
PictureDao::remove(const int& id) const
{
  QSqlQuery query(mDatabase);
  query.prepare("REMOVE FROM pictures WHERE id=:id");
  query.bindValue(":id", id);
  query.exec();
}

void
PictureDao::removeForAlbum(const int& albumId) const
{
  QSqlQuery query(mDatabase);
  query.prepare("REMOVE FROM pictures WHERE album_id=:albumId");
  query.bindValue(":albumId", albumId);
  query.exec();
}

std::unique_ptr<PictureVector>
PictureDao::list(const int& albumId) const
{
  QSqlQuery query("SELECT * FROM pictures WHERE album_id=:albumId", mDatabase);
  query.bindValue(":albumId", albumId);
  query.exec();

  auto list = std::make_unique<PictureVector>();
  while (query.next()) {
    auto picture = std::make_unique<Picture>();
    picture->setId(query.value("id").toInt());
    picture->setAlbumId(query.value("album_id").toInt());
    picture->setFileUrl(query.value("url").toString());
    list->push_back(std::move(picture));
  }

  return list;
}

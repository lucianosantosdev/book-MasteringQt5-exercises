#include "AlbumDao.h"
#include "Album.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QtDebug>

AlbumDao::AlbumDao(QSqlDatabase& database)
  : mDatabase(database)
{}

void
AlbumDao::init() const
{
  if (!mDatabase.tables().contains("albums")) {
    QSqlQuery query(mDatabase);
    bool ok = query.exec("CREATE TABLE albums ("
                         "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "  name TEXT"
                         ")");
    if (!ok) {
      qCritical() << "Database ERROR: Failed creating table albums";
    }
  }
}

void
AlbumDao::insert(Album& album) const
{
  QSqlQuery query(mDatabase);
  query.prepare("INSERT INTO albums (name) VALUES (:name)");
  query.bindValue(":name", album.name());

  bool ok = query.exec();
  if (!ok) {
    qCritical() << "Failed inserting into albums";
  }
  album.setId(query.lastInsertId().toInt());
}

void
AlbumDao::update(const Album& album) const
{
  QSqlQuery query(mDatabase);
  query.prepare("UPDATE albums  SET name=:name WHERE id=:id");
  query.bindValue(":name", album.name());
  query.bindValue(":id", album.id());
  query.exec();
}

void
AlbumDao::remove(int id) const
{
  QSqlQuery query(mDatabase);
  query.prepare("REMOVE FROM albums WHERE id=:id");
  query.bindValue(":id", id);
  query.exec();
}

QVector<Album*>
AlbumDao::list() const
{
  QSqlQuery query("SELECT * FROM albums", mDatabase);
  query.exec();
  QVector<Album*> list;
  while (query.next()) {
    Album* album = new Album();
    album->setId(query.value("id").toInt());
    album->setName(query.value("name").toString());
    list.append(album);
  }
  return list;
}

#pragma once

#include <QVector>

class QSqlDatabase;
class Album;

class AlbumDao
{
public:
  AlbumDao(QSqlDatabase& database);
  void init() const;
  void insert(Album& album) const;
  void update(const Album& album) const;
  void remove(int id) const;
  QVector<Album*> list() const;

private:
  QSqlDatabase& mDatabase;
};

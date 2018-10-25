#pragma once

#include "Album.h"

#include <memory>
#include <vector>

class QSqlDatabase;

typedef std::vector<std::unique_ptr<Album>> AlbumVector;

class AlbumDao
{
public:
  AlbumDao(QSqlDatabase& database);
  void init() const;
  void insert(Album& album) const;
  void update(const Album& album) const;
  void remove(int id) const;
  std::unique_ptr<AlbumVector> list() const;

private:
  QSqlDatabase& mDatabase;
};

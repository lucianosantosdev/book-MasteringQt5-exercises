#pragma once

#include "Picture.h"

#include <memory>
#include <vector>

class QSqlDatabase;

using PictureVector = std::vector<std::unique_ptr<Picture>>;
class PictureDao
{
public:
  PictureDao(QSqlDatabase& database);
  void init() const;
  void insert(const int& albumId, Picture& picture) const;
  void remove(const int& id) const;
  void removeForAlbum(const int& albumId) const;

  std::unique_ptr<PictureVector> list(const int& albumId) const;

private:
  QSqlDatabase& mDatabase;
};

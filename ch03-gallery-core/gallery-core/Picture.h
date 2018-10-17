#pragma once

#include <QString>
#include <QUrl>

#include "gallery-core_global.h"

class GALLERYCORESHARED_EXPORT Picture
{
public:
  Picture(const QString& filePath = "");
  Picture(const QUrl& fileUrl);

  int id() const;
  void setId(int id);

  int albumId() const;
  void setAlbumId(int albumId);

  QUrl fileUrl() const;
  void setFileUrl(const QUrl& fileUrl);

private:
  int mId;
  int mAlbumId;
  QUrl mFileUrl;
};

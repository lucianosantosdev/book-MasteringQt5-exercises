#pragma once

#include <QAbstractListModel>
#include <QHash>
#include <memory>
#include <vector>

#include "PictureDao.h"
#include "gallery-core_global.h"

class AlbumModel;
class DatabaseManager;

class GALLERYCORESHARED_EXPORT PictureModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum Roles
  {
    IdRole = Qt::UserRole + 1,
    FilePathRole
  };

  PictureModel(const AlbumModel& albumModel, QObject* parent = nullptr);

  QModelIndex addPicture(const Picture& picture);

  void setAlbumId(const int& albumId);
  void clearAlbum();

  // QAbstractItemModel interface
public:
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;

  bool removeRows(int row, int count, const QModelIndex& parent) override;

  QHash<int, QByteArray> roleNames() const override;

public slots:
  void deletePicturesForAlbum();

private:
  void loadPictures(const int& albumId);
  bool isValidIndex(const QModelIndex& index) const;

private:
  DatabaseManager& mDb;
  int mAlbumId;
  std::unique_ptr<PictureVector> mPictures;
};

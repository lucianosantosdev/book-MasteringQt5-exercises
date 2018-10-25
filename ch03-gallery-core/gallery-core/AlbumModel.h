#pragma once

#include <QAbstractListModel>
#include <QHash>
#include <memory>
#include <vector>

#include "AlbumDao.h"
#include "gallery-core_global.h"

class DatabaseManager;

class GALLERYCORESHARED_EXPORT AlbumModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum Roles
  {
    IdRole = Qt::UserRole + 1,
    NameRole
  };

  AlbumModel(QObject* parent = nullptr);

  QModelIndex addAlbum(const Album& album);

  // QAbstractItemModel interface
public:
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;

  bool setData(const QModelIndex& index,
               const QVariant& value,
               int role) override;

  bool removeRows(int row, int count, const QModelIndex& parent) override;

  QHash<int, QByteArray> roleNames() const override;

private:
  bool isValidIndex(const QModelIndex& index) const;

private:
  DatabaseManager& mDb;
  std::unique_ptr<AlbumVector> mAlbums;
};

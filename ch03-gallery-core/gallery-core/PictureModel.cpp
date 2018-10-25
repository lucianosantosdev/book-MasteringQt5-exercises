#include "PictureModel.h"
#include "AlbumModel.h"
#include "DatabaseManager.h"
#include "Picture.h"

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent)
  : QAbstractListModel(parent)
  , mDb(DatabaseManager::instance())
  , mAlbumId(-1)
  , mPictures(new PictureVector)
{
  connect(&albumModel,
          &AlbumModel::rowsRemoved,
          this,
          &PictureModel::deletePicturesForAlbum);
}

QModelIndex
PictureModel::addPicture(const Picture& picture)
{
  int rowIndex = rowCount();
  beginInsertRows(QModelIndex(), rowIndex, rowIndex);
  auto newPicture = std::make_unique<Picture>(picture);
  mDb.pictureDao().insert(mAlbumId, *newPicture);
  mPictures->push_back(std::move(newPicture));
  endInsertRows();
  return index(rowIndex, 0);
}

void
PictureModel::setAlbumId(const int& albumId)
{
  beginResetModel();
  mAlbumId = albumId;
  loadPictures(mAlbumId);
  endResetModel();
}

void
PictureModel::clearAlbum()
{
  setAlbumId(-1);
}

int
PictureModel::rowCount(const QModelIndex& parent) const
{
  (void)parent;
  return static_cast<int>(mPictures->size());
}

QVariant
PictureModel::data(const QModelIndex& index, int role) const
{
  if (!isValidIndex(index)) {
    return QVariant();
  }

  const Picture& picture = *mPictures->at(static_cast<ulong>(index.row()));
  switch (role) {
    case Roles::IdRole:
      return picture.id();
    case Roles::FilePathRole:
    case Qt::DisplayRole:
      return picture.fileUrl();
    default:
      return QVariant();
  }
}

bool
PictureModel::removeRows(int row, int count, const QModelIndex& parent)
{
  if (row < 0 || row > rowCount() || count < 0 || (row + count) > rowCount()) {
    return false;
  }

  beginRemoveRows(parent, row, row + count - 1);
  int countLeft = count;
  while (countLeft--) {
    const Picture& album = *mPictures->at(static_cast<ulong>(row + countLeft));
    mDb.albumDao().remove(album.id());
  }
  mPictures->erase(mPictures->begin() + row, mPictures->begin() + row + count);
  endRemoveRows();

  return true;
}

QHash<int, QByteArray>
PictureModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[Roles::IdRole] = "id";
  roles[Roles::FilePathRole] = "filepath";
  return roles;
}

void
PictureModel::deletePicturesForAlbum()
{}

void
PictureModel::loadPictures(const int& albumId)
{
  if (albumId <= 0) {
    mPictures.reset(new PictureVector);
    return;
  }
  mPictures = mDb.pictureDao().list(albumId);
}

bool
PictureModel::isValidIndex(const QModelIndex& index) const
{
  if (index.row() < 0 || index.row() >= rowCount() || !index.isValid()) {
    return false;
  }
  return true;
}

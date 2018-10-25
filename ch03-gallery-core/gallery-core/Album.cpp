#include "Album.h"
#include <QtDebug>

Album::Album(const QString& name)
  : mId(-1)
  , mName(name)
{}

Album::~Album()
{
  qDebug() << "~Album()";
}

int
Album::id() const
{
  return mId;
}

void
Album::setId(int id)
{
  mId = id;
}

QString
Album::name() const
{
  return mName;
}

void
Album::setName(const QString& name)
{
  mName = name;
}

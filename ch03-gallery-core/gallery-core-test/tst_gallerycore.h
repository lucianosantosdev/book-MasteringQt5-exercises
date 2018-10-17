#pragma once

#include "Album.h"
#include "DatabaseManager.h"
#include "Picture.h"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <string>

using namespace testing;

TEST(GalleryCore, GalleryCoreAlbumInitialize)
{
  QString name = "MeuAlbum";
  Album album(name);
  ASSERT_THAT(album.name(), Eq(name));
  ASSERT_THAT(album.id(), Eq(-1));

  DatabaseManager::instance().albumDao().insert(album);
  ASSERT_THAT(album.id(), Not(0));
}

TEST(GalleryCore, GalleryCorePictureInitialize)
{
  QString path = "/home";
  Picture pic(path);
  ASSERT_THAT(pic.fileUrl(), Eq(QUrl::fromLocalFile(path)));
  ASSERT_THAT(pic.id(), Eq(-1));
  ASSERT_THAT(pic.albumId(), Eq(-1));
}

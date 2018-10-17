#pragma once

#include <QtCore/qglobal.h>

#if defined(GALLERYCORE_LIBRARY)
#define GALLERYCORESHARED_EXPORT Q_DECL_EXPORT
#else
#define GALLERYCORESHARED_EXPORT Q_DECL_IMPORT
#endif

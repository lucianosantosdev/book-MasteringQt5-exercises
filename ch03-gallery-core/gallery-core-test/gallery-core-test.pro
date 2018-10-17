include(gtest_dependency.pri)

QT += sql
TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

HEADERS += \
        tst_gallerycore.h

SOURCES += \
        main.cpp

SOURCES += $$files(../gallery-core/*.cpp)
HEADERS += $$files(../gallery-core/*.h)
INCLUDEPATH += ../gallery-core

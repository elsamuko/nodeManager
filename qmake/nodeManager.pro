# Qt config
QT += core gui widgets

TARGET = nodeManager
TEMPLATE = app

macx:       PLATFORM=mac
win32:      PLATFORM=win
unix:!macx: PLATFORM=linux
unix:!macx: CONFIG += linux

MAIN_DIR = ..
PRI_DIR  = $${MAIN_DIR}/qmake/include
SRC_DIR  = $${MAIN_DIR}/src

include( $${PRI_DIR}/setup.pri )
DESTDIR  = $${MAIN_DIR}/bin/$${COMPILE_MODE}

include( $${PRI_DIR}/src.pri )
macx:  include( $${PRI_DIR}/mac.pri )
linux: include( $${PRI_DIR}/linux.pri )

macx:  QMAKE_POST_LINK += $$(QTDIR)/bin/macdeployqt "$${DESTDIR}/$${TARGET}.app";
win32: QMAKE_POST_LINK += $$(QTDIR)/bin/windeployqt "$${DESTDIR}/$${TARGET}.exe";

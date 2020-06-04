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

macx:  QMAKE_POST_LINK += $$(QTDIR)/bin/macdeployqt "$${DESTDIR}/$${TARGET}.app" ;
win32 {
    CRLF = $$escape_expand(\n\t)
    DESTDIR_WIN = $${DESTDIR}
    DESTDIR_WIN ~= s,/,\\,g
    FULL_TARGET = $${DESTDIR_WIN}\\$${TARGET}.exe
    QMAKE_POST_LINK += $$quote( echo \"Deploy...\" & $$(QTDIR)/bin/windeployqt \"$${FULL_TARGET}\" $$CRLF )
}

# logging
HEADERS +=  $${SRC_DIR}/log/log.hpp
SOURCES +=  $${SRC_DIR}/log/log.cpp

# header, which is precompiled and included automatically
CONFIG += precompile_header
PRECOMPILED_HEADER = $${SRC_DIR}/precompiled.hpp

# ui
SOURCES += $${SRC_DIR}/ui/main.cpp

HEADERS += $${SRC_DIR}/ui/mainwindow.hpp
SOURCES += $${SRC_DIR}/ui/mainwindow.cpp
FORMS   += $${SRC_DIR}/ui/mainwindow.ui

# graphics
HEADERS += $${SRC_DIR}/graphics/graphicsview.hpp
SOURCES += $${SRC_DIR}/graphics/graphicsview.cpp

HEADERS += $${SRC_DIR}/graphics/graphicsscene.hpp
SOURCES += $${SRC_DIR}/graphics/graphicsscene.cpp

HEADERS += $${SRC_DIR}/graphics/graphicstypes.hpp

HEADERS += $${SRC_DIR}/graphics/node.hpp
SOURCES += $${SRC_DIR}/graphics/node.cpp

HEADERS += $${SRC_DIR}/graphics/connection.hpp
SOURCES += $${SRC_DIR}/graphics/connection.cpp

# helper
HEADERS += $${SRC_DIR}/persistence.hpp
SOURCES += $${SRC_DIR}/persistence.cpp

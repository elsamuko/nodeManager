QMAKE_CXXFLAGS_RELEASE += -msse2 -Os -ffast-math -funsafe-math-optimizations
QMAKE_CXXFLAGS_DEBUG += -pg

QMAKE_LFLAGS_RELEASE += -flto
QMAKE_LFLAGS_DEBUG += -pg

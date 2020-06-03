QMAKE_CXXFLAGS_RELEASE += -msse2 -Os -ffast-math -funsafe-math-optimizations
QMAKE_CXXFLAGS_DEBUG += -pg

QMAKE_LFLAGS_RELEASE += -flto
QMAKE_LFLAGS_DEBUG += -pg

# use g++-10 on Ubuntu 20.04
# sudo apt install g++-10 gcc-10
QMAKE_CC = gcc-10
QMAKE_CXX = g++-10

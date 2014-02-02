TEMPLATE = lib

TARGET = QSimpleFileWatcher

QT += core

CONFIG += staticlib


HEADERS += ./qsimplefilewatcher.h \
    ./FileWatcher/FileWatcher.h \
    ./FileWatcher/FileWatcherImpl.h \
    ./FileWatcher/FileWatcherLinux.h \
    ./FileWatcher/FileWatcherOSX.h \
    ./FileWatcher/FileWatcherWin32.h
	
SOURCES += ./qsimplefilewatcher.cpp \
    ./FileWatcherLinux.cpp \
    ./FileWatcherOSX.cpp \
    ./FileWatcherWin32.cpp \
    ./FileWatcher.cpp


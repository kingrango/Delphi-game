QT += core widgets

CONFIG += c++17

TARGET = AdbDeviceManager
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    AdbClient.cpp \
    universalmethodhandler.cpp

HEADERS += \
    mainwindow.h \
    ui_mainwindow.h \
    AdbClient.h \
    universalmethodhandler.h

# Create data directory
data.path = $$OUT_PWD/data
data.files = data/*
INSTALLS += data

# For development, copy data directory
win32 {
    CONFIG(debug, debug|release) {
        DESTDIR = debug
    } else {
        DESTDIR = release
    }
    
    copydata.commands = $(COPY_DIR) \"$$PWD\\data\" \"$$OUT_PWD\\$$DESTDIR\\data\"
} else {
    copydata.commands = cp -r $$PWD/data $$OUT_PWD/
}

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
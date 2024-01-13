QT       += core gui charts serialport sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbserver.cpp \
    main.cpp \
    monitorwidget.cpp \
    monitorwindow.cpp \
    serialportserver.cpp \
    settingwidget.cpp \
    tabledataview.cpp

HEADERS += \
    dbserver.h \
    monitorwidget.h \
    monitorwindow.h \
    serialportserver.h \
    settingwidget.h \
    tabledataview.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

FORMS += \
    settingwidget.ui

QT       += core gui

QT       += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemy.cpp \
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    pause.cpp \
    scenegameover.cpp \
    sceneplay.cpp \
    sceneplay_02.cpp \
    secondmainwindow.cpp

HEADERS += \
    enemy.h \
    form.h \
    mainwindow.h \
    pause.h \
    scenegameover.h \
    sceneplay.h \
    sceneplay_02.h \
    secondmainwindow.h

FORMS += \
    form.ui \
    mainwindow.ui \
    pause.ui \
    scenegameover.ui \
    sceneplay.ui \
    secondmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc \
    res.qrc \
    sound.qrc

DISTFILES += \
    img/xingkong.jpg \
    sound/E4.wav

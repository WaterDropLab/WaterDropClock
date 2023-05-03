QT       += core gui
QT       +=texttospeech
QT       +=multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutme.cpp \
    configwindow.cpp \
    displaywindow.cpp \
    fontselecterdialog.cpp \
    frmdisplay.cpp \
    frmothers.cpp \
    frmreport.cpp \
    main.cpp \
    mainmenu.cpp \
    parfontselector.cpp \
    reportthread.cpp \
    startwindow.cpp

HEADERS += \
    aboutme.h \
    configwindow.h \
    displaywindow.h \
    fontselecterdialog.h \
    frmdisplay.h \
    frmothers.h \
    frmreport.h \
    mainmenu.h \
    parfontselector.h \
    reportthread.h \
    startwindow.h

FORMS += \
    aboutme.ui \
    configwindow.ui \
    displaywindow.ui \
    fontselecterdialog.ui \
    frmdisplay.ui \
    frmothers.ui \
    frmreport.ui \
    mainmenu.ui \
    parfontselector.ui \
    startwindow.ui

TRANSLATIONS += \
    WaterDropClock_zh_CN.ts \
    WaterDropClock_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    res.qrc
RC_ICONS=PS.ico

VERSION = 1.0.1

RC_LANG = 0x004

QMAKE_TARGET_COMPANY = WaterDrop Lab,org

QMAKE_TARGET_PRODUCT =WaterDropClock

QMAKE_TARGET_DESCRIPTION=WaterDrop Clock

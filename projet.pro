QT += core gui  sql
QT += sql
QT += core gui printsupport
QT += widgets
QT += charts
QT += multimedia
QT += network location quickwidgets
RES += RES.qrc

include("xlsx/qtxlsx.pri")
LIBS += -LC:/OpenSSL/win32/lib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += multimedia
CONFIG += c++11
QT       += charts
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
    connection.cpp \
    formateur.cpp \
    formation.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    connection.h \
    formateur.h \
    formation.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
LIBS += -LC:/OpenSSL-Win32/lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    RES.qrc \
    animationLogin.qrc \
    az.qrc \
    back.qrc \
    bg.qrc \
    cap.qrc \
    capt.qrc \
    captures.qrc \
    exportation.qrc \
    icons.qrc \
    image.qrc \
    images.qrc \
    img.qrc \
    insightify_interface_statsFinance.qrc \
    logo.qrc \
    logo_excel.qrc \
    logoo.qrc \
    photo.qrc \
    qml.qrc \
    sms.qrc \
    stat.qrc \
    tools.qrc \
    tri.qrc

DISTFILES +=

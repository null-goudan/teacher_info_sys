QT       += core gui sql

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

INCLUDEPATH += $$PWD m_tablewidget/
include($$PWD/m_tablewidget/m_tablewidget.pri)
INCLUDEPATH += $$PWD infoshow/
include($$PWD/infoshow/infoshow.pri)
INCLUDEPATH += $$PWD statistician/
include($$PWD/statistician/statistician.pri)
INCLUDEPATH += $$PWD updatewidget/
include($$PWD/updatewidget/updatewidget.pri)

SOURCES += \
    main.cpp \
    login.cpp \
    manager_admin.cpp \
    self_info.cpp \
    teacher_info_wight.cpp \
    work_info_wight.cpp

HEADERS += \
    login.h \
    manager_admin.h \
    self_info.h \
    teacher_info_wight.h \
    work_info_wight.h

FORMS += \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES +=

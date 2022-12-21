QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Engineer/engineermodel.cpp \
    main.cpp \
    qcustomplot.cpp \
    theme.cpp \
    viewdefault.cpp

HEADERS += \
    ../Engineer/engineercontroller.h \
    ../Engineer/engineermodel.h \
    ../Engineer/graphcontroller.h \
    creditcontroller.h \
    creditmodel.h \
    depositcontroller.h \
    depositmodel.h \
    qcustomplot.h \
    simplecontroller.h \
    simplemodel.h \
    theme.h \
    viewdefault.h

FORMS += \
    viewdefault.ui

#win32:RC_FILE = calculator_ico.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

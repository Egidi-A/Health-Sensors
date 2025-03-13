QT       += core gui
QT       += widgets
QT       += charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MODELLO/BPM.cpp \
    MODELLO/Ossigenazione.cpp \
    MODELLO/Sensore.cpp \
    MODELLO/SensoriCollection.cpp \
    MODELLO/Temperatura.cpp \
    MODELLO/modello.cpp \
    VIEW/dashboarddettagliwidget.cpp \
    VIEW/dashboardsensoriwidget.cpp \
    VIEW/dashboardsimulazionewidget.cpp \
    VIEW/healthdashboard.cpp \
    controller.cpp \
    filehandler.cpp \
    main.cpp
HEADERS += \
    MODELLO/BPM.h \
    MODELLO/Ossigenazione.h \
    MODELLO/Sensore.h \
    MODELLO/SensoriCollection.h \
    MODELLO/Temperatura.h \
    MODELLO/modello.h \
    VIEW/dashboarddettagliwidget.h \
    VIEW/dashboardsensoriwidget.h \
    VIEW/dashboardsimulazionewidget.h \
    VIEW/healthdashboard.h \
    controller.h \
    filehandler.h
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    MODELLO/note.txt

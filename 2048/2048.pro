TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core gui qml quick

SOURCES += \
        game.cpp \
        main.cpp

HEADERS += \
    game.h

DISTFILES += \
    Main.qml

RESOURCES += \
    qml.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T12:23:40
#
#-------------------------------------------------

# AUTHOR - Bala'zs Ko'ti (ktibalazs@gmail.com)


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Adafruit-OLED-emulator
TEMPLATE = app


SOURCES += main.cpp\
        emulator.cpp

HEADERS  += emulator.h \
    Adafruit_GFX.h \
    Adafruit_SSD1306.h \
    ArduiPi_SSD1306.h \
    example.h

RESOURCES += \
    emulator.qrc

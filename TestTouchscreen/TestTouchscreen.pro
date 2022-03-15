QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

# Defines for EasyLogging++
DEFINES += ELPP_NO_DEFAULT_LOG_FILE ELPP_QT_LOGGING

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    App/RenderArea/RenderArea.cpp \
    App/Touchscreen/ProfaceTouch.cpp \
    Communication/SerialPort/QSerialPort.cpp \
    Communication/SerialPort/SerialDebugWidget.cpp \
    Communication/SerialPort/qextserialbase.cpp \
    UI/MainWindow/MainWindow.cpp \
    UI/Paint/PaintWidget.cpp \
    Utility/Buffer/FifoBuffer.cpp \
    Utility/Buffer/LoopBuffer.cpp \
    Utility/Log/easyloggingpp/easylogging++.cc \
    App/main.cpp \
    Utility/QUtilityBox.cpp \
    Utility/Setting/QConfigSetting.cpp

HEADERS += \
    App/RenderArea/RenderArea.h \
    App/Touchscreen/ProfaceTouch.h \
    Communication/SerialPort/ComInitData.h \
    Communication/SerialPort/QSerialPort.h \
    Communication/SerialPort/SerialDebugWidget.h \
    Communication/SerialPort/qextserialbase.h \
    UI/MainWindow/MainWindow.h \
    UI/Paint/PaintWidget.h \
    Utility/Buffer/FifoBuffer.h \
    Utility/Buffer/LoopBuffer.h \
    Utility/Log/easyloggingpp/easylogging++.h \
    Utility/QUtilityBox.h \
    Utility/QtBaseType.h \
    Utility/Setting/QConfigSetting.h

FORMS += \
    Communication/SerialPort/SerialDebugWidget.ui \
    UI/MainWindow/MainWindow.ui \
    UI/Paint/PaintWidget.ui

win32{
    HEADERS += Communication/SerialPort/win_qextserialport.h
    SOURCES += Communication/SerialPort/win_qextserialport.cpp
}

unix{
    HEADERS += Communication/SerialPort/posix_qextserialport.h
    SOURCES += Communication/SerialPort/posix_qextserialport.cpp
}

RC_FILE = Resource/icon.rc

INCLUDEPATH += $$PWD/App
INCLUDEPATH += $$PWD/App/RenderArea
INCLUDEPATH += $$PWD/App/Touchscreen
INCLUDEPATH += $$PWD/Communication/SerialPort
INCLUDEPATH += $$PWD/UI
INCLUDEPATH += $$PWD/UI/MainWindow
INCLUDEPATH += $$PWD/UI/Paint
INCLUDEPATH += $$PWD/Utility
INCLUDEPATH += $$PWD/Utility/Buffer
INCLUDEPATH += $$PWD/Utility/Setting
INCLUDEPATH += $$PWD/Utility/Log
INCLUDEPATH += $$PWD/Utility/Log/easyloggingpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

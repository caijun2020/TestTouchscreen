/**********************************************************************
PACKAGE:        Touchscreen
FILE:           TouchAbs.cpp
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Touchscreen abstract class
**********************************************************************/


#include "TouchAbs.h"
#include <QDebug>

TouchAbs::TouchAbs() :
    serialPort(NULL),
    comDataBuffer(new QByteArray),
    screenHSize(1024),
    screenVSize(768),
    inputXMin(0),
    inputYMin(0),
    inputZMin(0),
    inputXMax(1023),
    inputYMax(1023),
    inputZMax(255),
    xPosInScreen(0),
    yPosInScreen(0),
    reverseCoordinateFlag(false),
    m_settingFile("config.ini")
{
    // Reserve buffer size
    comDataBuffer->reserve(BUFFER_SIZE);

    // Default setting file
    m_setting = new QConfigSetting(m_settingFile);

    // Load Settings from ini file
    loadSettingFromIniFile();
}

TouchAbs::~TouchAbs()
{
    delete comDataBuffer;
    delete m_setting;
}

void TouchAbs::bindModel(QSerialPort *portHandler)
{
    if(NULL != portHandler)
    {
        unbind();

        serialPort = portHandler;
        connect(serialPort, SIGNAL(newDataReady(QByteArray)), this, SLOT(updateIncomingData(QByteArray)));
    }
}

void TouchAbs::unbind()
{
    if(NULL != serialPort)
    {
        disconnect(serialPort, 0 , this , 0);
        serialPort = NULL;
    }
}

void TouchAbs::setScreenResolution(int hScreen, int vScreen)
{
    screenHSize = hScreen;
    screenVSize = vScreen;

    // Update to setting file
    updateSettingToFile();
}

int TouchAbs::getHScreen() const
{
    return screenHSize;
}

int TouchAbs::getVScreen() const
{
    return screenVSize;
}

void TouchAbs::updateIncomingData(QByteArray data)
{
    // Check buffer overflow
    if(comDataBuffer->size() + data.size() > BUFFER_SIZE)
    {
        comDataBuffer->clear();
    }
    comDataBuffer->append(data);

    // Parse touch data
    parseTouchData();
}

void TouchAbs::calTouchPosInScreen(int x, int y)
{
    if(!reverseCoordinateFlag)
    {
        xPosInScreen = (abs(x - inputXMin) * screenHSize) / abs(inputXMax - inputXMin);
        yPosInScreen = (abs(y - inputYMin) * screenVSize) / abs(inputYMax - inputYMin);
    }
    else
    {
        xPosInScreen = (abs(inputXMax - x) * screenHSize) / abs(inputXMax - inputXMin);
        yPosInScreen = (abs(inputYMax - y) * screenVSize) / abs(inputYMax - inputYMin);
    }
}

void TouchAbs::loadSettingFromIniFile()
{
    QString section = "Touchscreen";

    if(m_setting->isKeyExist(section, "HScreen"))
    {
        screenHSize = m_setting->getValue(section, "HScreen").toInt();
    }
    else
    {
        m_setting->setValue(section, "HScreen", screenHSize);
    }

    if(m_setting->isKeyExist(section, "VScreen"))
    {
        screenVSize = m_setting->getValue(section, "VScreen").toInt();
    }
    else
    {
        m_setting->setValue(section, "VScreen", screenVSize);
    }
}

void TouchAbs::updateSettingToFile()
{
    QString section = "Touchscreen";
    m_setting->setValue(section, "HScreen", screenHSize);
    m_setting->setValue(section, "VScreen", screenVSize);
}

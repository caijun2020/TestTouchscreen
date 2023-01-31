/**********************************************************************
PACKAGE:        Touchscreen
FILE:           ProfaceTouch.h
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Proface Touchscreen touch event report
**********************************************************************/

#ifndef PROFACETOUCH_H
#define PROFACETOUCH_H
#include <QObject>
#include <stdint.h>
#include "QSerialPort.h"
#include "QConfigSetting.h"

#define PROFACE_TOUCH_DATA_WITH_HEADER

class ProfaceTouch : public QObject
{
    Q_OBJECT
public:
    ProfaceTouch();
    virtual ~ProfaceTouch();

    /*-----------------------------------------------------------------------
    FUNCTION:		bindModel
    PURPOSE:		Bind a QSerialPort model
    ARGUMENTS:		QSerialPort *portHandler -- QSerialPort pointer
    RETURNS:		None
    -----------------------------------------------------------------------*/
    void bindModel(QSerialPort *portHandler);

    /*-----------------------------------------------------------------------
    FUNCTION:		unbind
    PURPOSE:		Unbind the QSerialPort model
    ARGUMENTS:		None
    RETURNS:		None
    -----------------------------------------------------------------------*/
    void unbind();

    /*-----------------------------------------------------------------------
    FUNCTION:		setScreenResolution
    PURPOSE:		Set the resolution of screen (such as 1024x768)
    ARGUMENTS:		int hScreen, horizontal resolution
                    int vScreen, vertical resolution
    RETURNS:		None
    -----------------------------------------------------------------------*/
    void setScreenResolution(int hScreen, int vScreen);

    /*-----------------------------------------------------------------------
    FUNCTION:		getHScreen
    PURPOSE:		Get horizontal screen size
    ARGUMENTS:		None
    RETURNS:		int, horizontal screen size
    -----------------------------------------------------------------------*/
    int getHScreen() const;

    /*-----------------------------------------------------------------------
    FUNCTION:		getVScreen
    PURPOSE:		Get vertical screen size
    ARGUMENTS:		None
    RETURNS:		int, vertical screen size
    -----------------------------------------------------------------------*/
    int getVScreen() const;

    enum PROFACE_TOUCH_HEADER_T
    {
        TOUCH_PRESSED = 0x11,
        TOUCH_RELEASED = 0x10
    };

#ifdef PROFACE_TOUCH_DATA_WITH_HEADER
    struct PROFACE_TOUCH_DATA_T
    {
        uint8_t header; // Always 0x11
        uint8_t xhi;    // High 8 bits of X
        uint8_t xlo;    // Low 8 bits of X
        uint8_t yhi;    // High 8 bits of Y
        uint8_t ylo;    // Low 8 bits of Y
    };

    struct PROFACE_RELEASED_DATA_T
    {
        uint8_t header; // Always 0x11
        uint8_t xhi;    // High 8 bits of X
        uint8_t xlo;    // Low 8 bits of X
        uint8_t yhi;    // High 8 bits of Y
        uint8_t ylo;    // Low 8 bits of Y
        uint8_t released;   // Always 0x10
    };
#else
    struct PROFACE_TOUCH_DATA_T
    {
        uint8_t xhi;    // High 8 bits of X
        uint8_t xlo;    // Low 8 bits of X
        uint8_t yhi;    // High 8 bits of Y
        uint8_t ylo;    // Low 8 bits of Y
    };

    struct PROFACE_RELEASED_DATA_T
    {
        uint8_t xhi;    // High 8 bits of X
        uint8_t xlo;    // Low 8 bits of X
        uint8_t yhi;    // High 8 bits of Y
        uint8_t ylo;    // Low 8 bits of Y
        uint8_t released;   // Always 0x10
    };
#endif

signals:
    void newTouchData(int x, int y, int z);

private slots:
    void updateIncomingData(QByteArray data);

private:
    enum
    {
        BUFFER_SIZE = 2000
    };

    QSerialPort *serialPort;    // COM port handler
    struct COM_PORT_INIT_DATA *comInitData; // COM port init data

    QByteArray *comDataBuffer;      //data buffer to store the data from the com port

    int screenHSize;            //screen horizontal size
    int screenVSize;            //screen vertical size

    int inputXMin;
    int inputYMin;
    int inputZMin;

    int inputXMax;
    int inputYMax;
    int inputZMax;

    int xPosInScreen;   //real X position in the screen
    int yPosInScreen;   //real Y position in the screen

    bool reverseCoordinateFlag; // Flag used to reverse coordinate

    QString m_settingFile;
    QConfigSetting *m_setting;   // Ini file Setting handler

    // Parse touch input data
    void parseTouchData();

    // Load setting from ini file
    void loadSettingFromIniFile();

    // Update setting to ini file
    void updateSettingToFile();

    // Convert touch data to screen pos
    void calTouchPosInScreen(int x, int y);
};

#endif // PROFACETOUCH_H

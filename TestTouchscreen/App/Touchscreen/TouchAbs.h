/**********************************************************************
PACKAGE:        Touchscreen
FILE:           TouchAbs.h
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Touchscreen abstract class
**********************************************************************/

#ifndef TOUCHABS_H
#define TOUCHABS_H
#include <QObject>
#include <stdint.h>
#include "QSerialPort.h"
#include "QConfigSetting.h"


class TouchAbs : public QObject
{
    Q_OBJECT
public:
    TouchAbs();
    virtual ~TouchAbs();

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

signals:
    void newTouchData(int x, int y, int z);

protected slots:
    void updateIncomingData(QByteArray data);

protected:
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
    virtual void parseTouchData() = 0;

    // Load setting from ini file
    void loadSettingFromIniFile();

    // Update setting to ini file
    void updateSettingToFile();

    // Convert touch data to screen pos
    void calTouchPosInScreen(int x, int y);
};

#endif // TOUCHABS_H

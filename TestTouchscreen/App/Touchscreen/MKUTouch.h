/**********************************************************************
PACKAGE:        Touchscreen
FILE:           MKUTouch.h
COPYRIGHT (C):  All rights reserved.

PURPOSE:        MKU Touchscreen touch event report
**********************************************************************/

#ifndef MKUTOUCH_H
#define MKUTOUCH_H
#include <QObject>
#include <stdint.h>
#include "QSerialPort.h"
#include "QConfigSetting.h"
#include "TouchAbs.h"

class MKUTouch : public TouchAbs
{
    Q_OBJECT
public:
    MKUTouch();
    virtual ~MKUTouch();

    enum MKU_TOUCH_HEADER_T
    {
        TOUCH_PRESSED = 0x81,
        TOUCH_RELEASED = 0x80
    };

    struct MKU_TOUCH_DATA_T
    {
        uint8_t header; // Pressed:0x81, Released:0x80
        uint8_t xhi;    // High 8 bits of X
        uint8_t xlo;    // Low 8 bits of X
        uint8_t yhi;    // High 8 bits of Y
        uint8_t ylo;    // Low 8 bits of Y
    };

protected:

    // Parse touch input data
    virtual void parseTouchData();
};

#endif // MKUTOUCH_H

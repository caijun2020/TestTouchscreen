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
#include "TouchAbs.h"

#define PROFACE_TOUCH_DATA_WITH_HEADER

class ProfaceTouch : public TouchAbs
{
    Q_OBJECT
public:
    ProfaceTouch();
    virtual ~ProfaceTouch();

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

protected:

    // Parse touch input data
    virtual void parseTouchData();
};

#endif // PROFACETOUCH_H

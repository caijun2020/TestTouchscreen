/**********************************************************************
PACKAGE:        Touchscreen
FILE:           MKUTouch.cpp
COPYRIGHT (C):  All rights reserved.

PURPOSE:        MKU Touchscreen touch event report
**********************************************************************/

#include "MKUTouch.h"
#include <QDebug>

#define MKU_TOUCH_DEBUG_TRACE

MKUTouch::MKUTouch()
{
    inputXMin = 0;
    inputYMin = 4095;
    inputZMin = 0;

    inputXMax = 4095;
    inputYMax = 0;
    inputZMax = 255;
}

MKUTouch::~MKUTouch()
{
}

void MKUTouch::parseTouchData()
{
    while(comDataBuffer->size() >= (int)sizeof(struct MKU_TOUCH_DATA_T))
    {
        MKU_TOUCH_DATA_T *touchPacket = (MKU_TOUCH_DATA_T *)comDataBuffer->data();

        if((TOUCH_PRESSED == touchPacket->header) || (TOUCH_RELEASED == touchPacket->header))
        {
            int xPos = touchPacket->xhi * 256 + touchPacket->xlo;
            int yPos = touchPacket->yhi * 256 + touchPacket->ylo;
            int zPos = 255;
            bool outOfRange = false;

            if(TOUCH_RELEASED == touchPacket->header)
            {
                // When z = 0 means touch released!
                zPos = 0;
            }

            // Remove the parsed data from buffer
            comDataBuffer->remove(0, sizeof(struct MKU_TOUCH_DATA_T));

            if(xPos > inputXMax)
            {
                xPos = inputXMax;
                outOfRange = true;
            }
            else if(xPos < inputXMin)
            {
                xPos = inputXMin;
                outOfRange = true;
            }

            // MKU touch, inputYMin = 4095, inputYMax = 0, so here the check condition shall be
            // yPos < inputYMax, out of range, and yPos > inputYMin, out of range
            if(yPos < inputYMax)
            {
                yPos = inputYMax;
                outOfRange = true;
            }
            else if(yPos > inputYMin)
            {
                yPos = inputYMin;
                outOfRange = true;
            }

            if(zPos > inputZMax)
            {
                zPos = inputZMax;
                outOfRange = true;
            }
            else if(zPos < inputZMin)
            {
                zPos = inputZMin;
                outOfRange = true;
            }

        #ifdef MKU_TOUCH_DEBUG_TRACE
            qDebug() << "MKUTouch::parseTouchData() X =" << xPos;
            qDebug() << "MKUTouch::parseTouchData() Y =" << yPos;
            qDebug() << "MKUTouch::parseTouchData() Z =" << zPos;
        #endif

            if(!outOfRange)
            {
                // Convert to screen pos
                calTouchPosInScreen(xPos, yPos);

                // Emit signal
                emit newTouchData(xPosInScreen, yPosInScreen, zPos);
            }
        }
        else
        {
            // Remove 1 bytes and parse next data(begin from touch header 0x11)
            comDataBuffer->remove(0, 1);
        }
    }
}

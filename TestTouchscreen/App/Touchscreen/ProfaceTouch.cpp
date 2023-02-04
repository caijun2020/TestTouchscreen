/**********************************************************************
PACKAGE:        Touchscreen
FILE:           ProfaceTouch.cpp
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Proface Touchscreen touch event report
**********************************************************************/

#include "ProfaceTouch.h"
#include <QDebug>

#define PROFACE_TOUCH_DEBUG_TRACE

ProfaceTouch::ProfaceTouch()
{
    inputXMin = 0;
    inputYMin = 0;
    inputZMin = 0;

    inputXMax = 1023;
    inputYMax = 1023;
    inputZMax = 255;
}

ProfaceTouch::~ProfaceTouch()
{
}

#ifdef PROFACE_TOUCH_DATA_WITH_HEADER
void ProfaceTouch::parseTouchData()
{
    while(comDataBuffer->size() >= (int)sizeof(struct PROFACE_TOUCH_DATA_T))
    {
        PROFACE_TOUCH_DATA_T *touchPacket = (PROFACE_TOUCH_DATA_T *)comDataBuffer->data();

        if((TOUCH_PRESSED == touchPacket->header))
        {
            int xPos = touchPacket->xhi * 256 + touchPacket->xlo;
            int yPos = touchPacket->yhi * 256 + touchPacket->ylo;
            int zPos = 255;
            bool outOfRange = false;

            if(comDataBuffer->size() >= (int)sizeof(struct PROFACE_RELEASED_DATA_T))
            {
                PROFACE_RELEASED_DATA_T *releasedPacket = (PROFACE_RELEASED_DATA_T *)comDataBuffer->data();

                if(TOUCH_RELEASED == releasedPacket->released)
                {
                    // When z = 0 means touch released!
                    zPos = 0;

                    // Remove the parsed data from buffer
                    comDataBuffer->remove(0, sizeof(struct PROFACE_RELEASED_DATA_T));
                }
                else
                {
                    // Remove the parsed data from buffer
                    comDataBuffer->remove(0, sizeof(struct PROFACE_TOUCH_DATA_T));
                }
            }
            else
            {
                // Remove the parsed data from buffer
                comDataBuffer->remove(0, sizeof(struct PROFACE_TOUCH_DATA_T));
            }

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

            if(yPos > inputYMax)
            {
                yPos = inputYMax;
                outOfRange = true;
            }
            else if(yPos < inputYMin)
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

        #ifdef PROFACE_TOUCH_DEBUG_TRACE
            qDebug() << "ProfaceTouch::parseTouchData() X =" << xPos;
            qDebug() << "ProfaceTouch::parseTouchData() Y =" << yPos;
            qDebug() << "ProfaceTouch::parseTouchData() Z =" << zPos;
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
#else
void ProfaceTouch::parseTouchData()
{
    int xPos = 0;
    int yPos = 0;
    int zPos = 255;

    while(comDataBuffer->size() >= (int)sizeof(struct PROFACE_RELEASED_DATA_T))
    {
        bool outOfRange = false;

        if(comDataBuffer->endsWith(TOUCH_RELEASED))
        {
            int size = comDataBuffer->size();
            int pos = size - sizeof(struct PROFACE_RELEASED_DATA_T);

            PROFACE_TOUCH_DATA_T *touchPacket = (PROFACE_TOUCH_DATA_T *)(comDataBuffer->data() + pos);

            xPos = touchPacket->xhi * 256 + touchPacket->xlo;
            yPos = touchPacket->yhi * 256 + touchPacket->ylo;

            comDataBuffer->remove(pos, sizeof(struct PROFACE_TOUCH_DATA_T));

            if(comDataBuffer->size() < (int)sizeof(struct PROFACE_RELEASED_DATA_T))
            {
                // When z = 0 means touch released!
                zPos = 0;

                comDataBuffer->clear();
            }
            else
            {
                zPos = 255;
            }

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

            if(yPos > inputYMax)
            {
                yPos = inputYMax;
                outOfRange = true;
            }
            else if(yPos < inputYMin)
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

        #ifdef PROFACE_TOUCH_DEBUG_TRACE
            qDebug() << "ProfaceTouch::parseTouchData() X =" << xPos;
            qDebug() << "ProfaceTouch::parseTouchData() Y =" << yPos;
            qDebug() << "ProfaceTouch::parseTouchData() Z =" << zPos;
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
            break;
        }

    }
}
#endif


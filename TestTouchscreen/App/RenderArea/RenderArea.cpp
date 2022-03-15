/**********************************************************************
PACKAGE:        UI
FILE:           RenderArea.h
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Render Widget to draw track
**********************************************************************/
#include <QtGui>

#include "RenderArea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    pWidget(parent),
    maxPoints(10000),
    displayPointsCnt(0),
    onceTouchPointsCnt(0),
    inputXMax(1024),
    inputYMax(768),
    displayType(Line)
{
    curPoint = new QPoint;
    totalPoints = new QPoint[maxPoints];
    onceTouchPoints = new int32_t[maxPoints];

    pen = new QPen;
    brush = new QBrush;
    pen->setColor(Qt::red);

    //setBackgroundRole(QPalette::Base);
    //setAutoFillBackground(true);

    this->resize(parent->width(), parent->height());

    //qDebug() << "Widget X=" << parent->width();
    //qDebug() << "widget Y=" << parent->height();

    //painter = new QPainter( parent );
}
RenderArea::~RenderArea()
{
    delete pen;
    delete brush;
    delete curPoint;
    delete[] totalPoints;
    delete[] onceTouchPoints;
}

void RenderArea::setXYRange(int32_t xMax, int32_t yMax)
{
    inputXMax = xMax;
    inputYMax = yMax;
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if(NULL == pWidget)
    {
        return;
    }

    this->resize(pWidget->width(), pWidget->height());

    QPainter painter(this);
    painter.setPen(*pen);
    painter.setBrush(*brush);

    if(Points == displayType)
    {
        painter.drawPoints(totalPoints, displayPointsCnt);
    }
    else if(Line == displayType)
    {
        for(int i = 0; i < (displayPointsCnt - 1); i++)
        {
            bool skipFlag = false;
            for(int j = 0; j < onceTouchPointsCnt; j++)
            {
                if(i == onceTouchPoints[j])
                {
                    skipFlag = true;
                    break;
                }
            }

            if(!skipFlag)
            {
                painter.drawLine(totalPoints[i], totalPoints[i+1]);
            }
            else
            {
                painter.drawPoint(totalPoints[i]);
            }
        }
    }

    //qDebug() << "draw point x=" << curPoint->x();
    //qDebug() << "draw point y=" << curPoint->y();
}

void RenderArea::updateTouchPoint(int xPos, int yPos)
{
    // Map to current widget
    curPoint->setX(xPos * this->width() / inputXMax);
    curPoint->setY(yPos * this->height() / inputYMax);

    // If display point overflow, clear screen
    if(displayPointsCnt >= maxPoints)
    {
        eraseDisplay();
    }

    totalPoints[displayPointsCnt++] = *curPoint;

    update();
}


void RenderArea::updateDisplay()
{
    update();
}

void RenderArea::eraseDisplay()
{
    displayPointsCnt = 0;
    onceTouchPointsCnt = 0;
    update();
}

void RenderArea::onceTouchDone()
{
    if(displayPointsCnt != 0)  //if the touch buffer is full, then we assume that there is no once touch done point
    {
        // If display point overflow, clear screen
        if(onceTouchPointsCnt >= maxPoints)
        {
            eraseDisplay();
        }

        onceTouchPoints[onceTouchPointsCnt++] = displayPointsCnt - 1;   //record the touch release point count

        //qDebug() << "onceTouchPoints=" << displayPointsCnt - 1;
        //qDebug() << "onceTouchPointsCnt=" << onceTouchPointsCnt;
    }

    update();
}

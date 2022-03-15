/**********************************************************************
PACKAGE:        UI
FILE:           RenderArea.h
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Render Widget to draw track
**********************************************************************/

#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QPainter>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                 Chord, Pie, Path, Text, Pixmap };

    RenderArea(QWidget *parent = 0);
    virtual ~RenderArea();

    void setXYRange(int32_t xMax, int32_t yMax);

public slots:
    void updateTouchPoint(int xPos, int yPos);

    void updateDisplay();
    void eraseDisplay();
    void onceTouchDone();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QWidget *pWidget;

    int32_t maxPoints;

    QPoint *curPoint;
    QPoint *totalPoints;

    int32_t displayPointsCnt;   //the count of points to be displayed

    QPen *pen;
    QBrush *brush;

    int32_t onceTouchPointsCnt;
    int32_t *onceTouchPoints;

    int32_t inputXMax;
    int32_t inputYMax;

    Shape displayType;

    //QPainter *painter;
};

#endif

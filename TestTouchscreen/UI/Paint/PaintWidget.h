/**********************************************************************
PACKAGE:        UI
FILE:           PaintWidget.h
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Paint Widget
**********************************************************************/

#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include "RenderArea.h"

namespace Ui {
class PaintWidget;
}

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = nullptr);
    virtual ~PaintWidget();

    void setXYRange(int32_t xMax, int32_t yMax);

private slots:
    void updateCoordinate(int x, int y, int z);

    void on_pushButton_clearScreen_clicked();

    void on_checkBox_reverse_clicked(bool checked);

private:
    Ui::PaintWidget *ui;

    RenderArea *m_renderArea;

    int screenHSize;            //screen horizontal size
    int screenVSize;            //screen vertical size

    bool reverseCoordinateFlag; // Flag used to reverse coordinate

    // Init UI
    void initUI();
};

#endif // PAINTWIDGET_H
